using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Collections.ObjectModel;
using System.Windows.Media.Imaging;

namespace Metis
{
    public partial class SelectShadow : PhoneApplicationPage
    {
        public ObservableCollection<ShadowDataModel> shadowModel = new ObservableCollection<ShadowDataModel>();
        public SelectShadow()
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
        }

        private void SelectShadowDone(object sender, System.EventArgs e)
        {
            List<ShadowDataModel> shadows = new List<ShadowDataModel>(); ;
        	// TODO: Add event handler implementation here.
            foreach ( ShadowDataModel sdm in ShadowList.SelectedItems)
                shadows.Add(sdm);
            App.ObjectNavigationData = new MetisNavigation(MetisNavigation.STATUS.SelectShadow, shadows);
            NavigationService.Navigate(new Uri("/CreateSecret.xaml", UriKind.RelativeOrAbsolute));
        }
    }
}