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
using System.Windows.Media;
 
namespace Metis
{
    public partial class CreateShadow : PhoneApplicationPage
    {
        System.IO.Stream ImageStream;
        BitmapImage ImageData;
        public CreateShadow()
        {
            InitializeComponent();
        }

        void pt_Completed(object sender, PhotoResult e)
        {
            if (e.TaskResult == TaskResult.OK)
            {
                ImageBrush imageBrush = new ImageBrush ();
                ImageData = new BitmapImage();
                ImageData.SetSource(e.ChosenPhoto);
                imageBrush.ImageSource = ImageData;
                ChooseSecretBtt.Background = imageBrush;
            }
        }

        private void ChooseSecret_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            PhotoChooserTask pt = new PhotoChooserTask();
            pt.Show();
            pt.Completed += pt_Completed;
        }

        private void Next_Click(object sender, System.EventArgs e)
        {
            if ( ImageData == null)
            {
                MessageBox.Show("Image cannot be empty");
                return;
            }

            if (numShadowCreateTxt.Text == "" | Convert.ToInt32(numShadowCreateTxt.Text) == 0)
            {
                MessageBox.Show("Number of shadow created cannot be empty or 0");
                return;
            }

            if (NumShadowMinTxt.Text == "" | Convert.ToInt32(NumShadowMinTxt.Text) == 0)
            {
                MessageBox.Show("Number of shadow minimum for creation cannot be empty or 0");
                return;
            }

            if (Convert.ToInt32(numShadowCreateTxt.Text) < Convert.ToInt32(NumShadowMinTxt.Text))
            {
                MessageBox.Show("Number of shadow created cannot be less than shadow minimum for creation");
                return;
            }

            MetisNavigation setting = new MetisNavigation
                (MetisNavigation.STATUS.Create ,ImageData, Convert.ToInt32(numShadowCreateTxt.Text), Convert.ToInt32(NumShadowMinTxt.Text));
            App.ObjectNavigationData = setting;
            NavigationService.Navigate( new Uri( "/ProgressPage.xaml", UriKind.RelativeOrAbsolute));
        }
    }
}