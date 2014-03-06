using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Microsoft.Phone.Tasks;
using System.Windows.Media.Imaging;
using System.Collections.ObjectModel;

namespace Metis
{
    public partial class CreateSecret : PhoneApplicationPage
    {
        public ObservableCollection<ShadowDataModel> shadowModel = new ObservableCollection<ShadowDataModel>();
        IList<MetisDll.Image> shadows = new List<MetisDll.Image>();
        ApplicationBarIconButton bttDone;
        public CreateSecret()
        {
            InitializeComponent();
            string[] list = ImageHelper.LoadShadowList();
            BitmapImage[] bmp = ImageHelper.LoadShadowImageList();
            for (int i = 0; i < list.Length; i++ )
            {
                shadowModel.Add(new ShadowDataModel(bmp[i],list[i]));
            }
            ShadowList.DataContext = shadowModel;
            ShadowList.EnforceIsSelectionEnabled = true;

            bttDone = new ApplicationBarIconButton();
            bttDone.IconUri = new Uri("/Assets/AppBar/check.png", UriKind.RelativeOrAbsolute);
            bttDone.Text = "done";
            bttDone.IsEnabled = false;
            bttDone.Click += CreateSecretDone_Click;
            ApplicationBar.Buttons.Add(bttDone);
        }
  

        private void CreateSecretDone_Click(object sender, System.EventArgs e)
        {
            List<MetisDll.Image> shadows = new List<MetisDll.Image>();
            foreach (ShadowDataModel sdm in ShadowList.SelectedItems)
            {
                WriteableBitmap wb =  new WriteableBitmap(sdm.ShadowImage);
                shadows.Add(new MetisDll.Image(wb.Pixels, wb.PixelWidth, wb.PixelHeight));
            }
            MetisNavigation navigation = new MetisNavigation(MetisNavigation.STATUS.Retrieve, shadows);
            App.ObjectNavigationData = navigation;
            NavigationService.Navigate(new Uri("/ProgressPage.xaml", UriKind.RelativeOrAbsolute));
        }

        private void OnPictureItemTap(object sender, EventArgs e)
        {
            
        }

        private void SelectionChanged(object sender, System.Windows.Controls.SelectionChangedEventArgs e)
        {
        	// TODO: Add event handler implementation here.
            TotalShadowSelectedTxt.Text = ShadowList.SelectedItems.Count.ToString();
            if (ShadowList.SelectedItems.Count == 0)
                bttDone.IsEnabled = false;
            else
                bttDone.IsEnabled = true;
        }
    }
}