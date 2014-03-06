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
using System.Windows.Media;

namespace Metis
{
    public partial class Finish : PhoneApplicationPage
    {
        public Finish()
        {
            InitializeComponent();
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            MetisNavigation mt = (MetisNavigation)App.ObjectNavigationData;
            if ( mt.status ==  MetisNavigation.STATUS.Retrieve)
            {
                BitmapImage wb;
                wb = ImageHelper.ConvertToBitmap(mt.secretImage);
               
                ImageResult.Visibility = Visibility.Visible;
                ImageResult.Source =  wb as ImageSource; 
            }
            base.OnNavigatedTo(e);
        }
        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            
            base.OnNavigatedFrom(e);
        }
        protected override void OnBackKeyPress(System.ComponentModel.CancelEventArgs e)
        {
            NavigationService.Navigate(new Uri("/Menu.xaml", UriKind.RelativeOrAbsolute));
            base.OnBackKeyPress(e);
        }
    }
}