using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Windows.Media.Imaging;
using System.IO;
using NFCTalk;
using Microsoft.Phone.Tasks;

namespace Metis
{
    public partial class NFCShadow : PhoneApplicationPage
    {
        private NFCTalk.DataContext _dataContext = NFCTalk.DataContext.Singleton;
        private List<ShadowDataModel> ShadowReceived = new List<ShadowDataModel>();
        private ProgressIndicator _progressIndicator = new ProgressIndicator();
        MetisNavigation setting;
        bool doneSend = false;
        public NFCShadow()
        {
            InitializeComponent();


        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

 

            _dataContext.Communication.ConnectivityProblem += ConnectivityProblem;
            _dataContext.Communication.ConnectionInterrupted += ConnectionInterrupted;

            _dataContext.Communication.Start();
            _dataContext.Communication.Connected += Connected;
            _dataContext.Communication.Connecting += Connecting;
            _dataContext.Communication.MessageReceived += Received;
            _dataContext.Communication.ConnectionInterrupted += Interrupted;

  
            setting =  (MetisNavigation)App.ObjectNavigationData;
            
        
            
        }
        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            base.OnNavigatedFrom(e);
            setting.sdm = ShadowReceived;
            App.ObjectNavigationData = setting;
            _dataContext.Communication.Connected -= Connected;
            _dataContext.Communication.Connecting -= Connecting;
            _dataContext.Communication.MessageReceived -= Received;
            _dataContext.Communication.ConnectionInterrupted -= Interrupted;
            _dataContext.Communication.ConnectivityProblem -= ConnectivityProblem;
            _dataContext.Communication.ConnectionInterrupted -= ConnectionInterrupted;

            _dataContext.Communication.Stop();

        
        }
        private void ConnectivityProblem()
        {
            _dataContext.Communication.Stop();
            _dataContext.Communication.Start();

            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                MessageBoxResult r = MessageBox.Show("Would you like to make sure that Bluetooth has been turned on?", "Unable to connect", MessageBoxButton.OKCancel);

                if (r.HasFlag(MessageBoxResult.OK))
                {
                    ConnectionSettingsTask connectionSettingsTask = new ConnectionSettingsTask();
                    connectionSettingsTask.ConnectionSettingsType = ConnectionSettingsType.Bluetooth;
                    connectionSettingsTask.Show();
                }
                else
                {
                    NavigationService.GoBack();
                }
            });
        }

        private void ConnectionInterrupted()
        {
            _dataContext.Communication.Stop();
            _dataContext.Communication.Start();
        }

        private void Connecting()
        {
            Deployment.Current.Dispatcher.BeginInvoke(async () =>
                 {
                     ShowProgress("connecting...");
                 });
        }

        private async void Connected()
        {
            Deployment.Current.Dispatcher.BeginInvoke(async() =>
            {
                if (setting.status == MetisNavigation.STATUS.Receive)
                    return;
                ShowProgress("Sending");
                List<ShadowDataModel> bmps = setting.sdm;
                if (setting.status == MetisNavigation.STATUS.Send)
                {
                    foreach (ShadowDataModel bmp in bmps)
                    {
                        NFCTalk.Message m = new NFCTalk.Message();
                        WriteableBitmap wb = new WriteableBitmap(bmp.ShadowImage);
                        MemoryStream ms = new MemoryStream();
                        wb.WritePNG(ms);
                        m.ImageBytes = ms.ToArray();
                        m.ImageName = bmp.LineOne;
                        await _dataContext.Communication.SendMessageAsync(m);
                    }
                    ShowProgress("Done");
                }
                
            });
            doneSend = true;
        }
        private void Interrupted()
        {
            if (doneSend)
                return;
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                ShowProgress("Interrupted :(");
            });
            ShadowReceived = null;
        }
        private void Received(Message m)
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                ShowProgress("Receiving");
                BitmapImage bm = new BitmapImage();
                MemoryStream ms = new MemoryStream(m.ImageBytes);
                bm.SetSource(ms);
                ImageHelper.SaveShadow(bm, m.ImageName);
                ShowProgress("Done");

                ShadowReceived.Add(new ShadowDataModel(bm, m.ImageName));
                setting.status = MetisNavigation.STATUS.Received;
                doneSend = true;
            });
                
        }
        /// <summary>
        /// Show system tray progress indicator.
        /// </summary>
        /// <param name="msg">Text to show</param>
        private void ShowProgress(String msg)
        {
            
                this.StatusText.Text = msg;
            
        }

        /// <summary>
        /// Hide system tray progress indicator.
        /// </summary>
        private void HideProgress()
        {
            _progressIndicator.IsVisible = false;

            SystemTray.SetProgressIndicator(this, _progressIndicator);
        }
    }
}