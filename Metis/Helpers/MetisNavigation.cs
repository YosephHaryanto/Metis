using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace Metis
{
    class MetisNavigation
    {
        public enum STATUS { Create, Retrieve,Send,Receive ,Received} ;

        public BitmapImage Image;
        public List<ShadowDataModel> sdm;

        public int numShadowCreated;
        public int numShadowMin;

        public STATUS status;

        public IList<MetisDll.Image> shadows;
        public MetisDll.Image secretImage;
      
        public MetisNavigation(STATUS status, BitmapImage Image, int numShadowCreated, int numShadowMin)
        {
            this.status = status;
            this.Image = Image;
            this.numShadowCreated = numShadowCreated;
            this.numShadowMin = numShadowMin;
        }

        public MetisNavigation(STATUS status, IList<MetisDll.Image> shadows)
        {
            this.status = status;
            this.shadows = shadows;
        }
        public MetisNavigation(BitmapImage image)
        {
            this.Image = image;
        }

        public MetisNavigation(STATUS status, List<ShadowDataModel> sdm)
        {
            this.status = status;
            this.sdm = sdm;
        }
    }
}
