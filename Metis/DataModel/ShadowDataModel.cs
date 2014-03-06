using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace Metis
{
    public class ShadowDataModel:INotifyPropertyChanged

    {
        public BitmapImage ShadowImage { get; set; }

        private String _LineOne;
        public String LineOne 
        { 
            get
            {
                return _LineOne;
            }
            
            set 
            {
                if (_LineOne == value)
                    return;
                if (value.Length < 4 | value.ToString().Substring(value.Length - 4, 4) != ".png")
                    value = value + ".png";
                ImageHelper.RenameShadow(_LineOne, value);
                _LineOne = value;
                
                OnPropertyChanged("LineOne");
            }
        }

        public String LineTwo { get; set; }

        public ShadowDataModel(BitmapImage ShadowImage, String LineOne)
        {
            this.ShadowImage = ShadowImage;
            this.LineOne = LineOne;
        }
        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null) PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}
