using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using System.Threading.Tasks;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Threading;
using MetisDll;
using System.Windows.Media.Imaging;

namespace Metis
{
    public partial class ProgressPage : PhoneApplicationPage
    {
        SecretSharingManager secretSharingManager; 
        Progress<int> progress;
        MetisNavigation setting;
        MetisDll.Image secret;
        public ProgressPage()
        {
            InitializeComponent();
            secretSharingManager = new SecretSharingManager();
            progress = new Progress<int>();
            progress.ProgressChanged += (sender, e) => { ProgressBarPage.Value = e; };
        }

        protected override async void OnNavigatedTo(NavigationEventArgs e)
        {
            setting = (MetisNavigation)App.ObjectNavigationData;
            if (setting.status == MetisNavigation.STATUS.Create )
            {
               Task<IList<MetisDll.Image>> returnedShadows = CreateShadow();
               IList<MetisDll.Image> shadows = await returnedShadows;

               int ctr = ImageHelper.LoadShadowList().Length;
               foreach (MetisDll.Image img in shadows)
                {
                    ImageHelper.SaveShadow(img,"shadow" + ctr.ToString() +".png");
                    ctr++;
                }
               NavigationService.Navigate(new Uri("/Finish.xaml", UriKind.RelativeOrAbsolute));
            }

            else if ( setting.status ==  MetisNavigation.STATUS.Retrieve)
            {
                Task<MetisDll.Image> returnedSecret = CreateSecret();
                secret = await returnedSecret;
                setting.secretImage = secret;
                ImageHelper.SaveImage(secret, "secretimage");
                NavigationService.Navigate(new Uri("/Finish.xaml", UriKind.RelativeOrAbsolute));
            }
            base.OnNavigatedTo(e);
        }

        private async Task<IList<MetisDll.Image>> CreateShadow()
        {
            MetisDll.Image secret = new MetisDll.Image
                (ImageHelper.GetPixelFromImage(setting.Image), setting.Image.PixelWidth, setting.Image.PixelHeight);

            IList<MetisDll.Image> shadows = 
                await secretSharingManager.CreateShadow(secret, setting.numShadowCreated, setting.numShadowMin).AsTask(progress);

            return shadows;
        }

        private async Task<MetisDll.Image> CreateSecret()
        {
            List<MetisDll.Image> sh =(List<MetisDll.Image>)setting.shadows;
            MetisDll.Image secret= await secretSharingManager.CreateSecret(sh).AsTask(progress);
            return secret;
        }
    }
}