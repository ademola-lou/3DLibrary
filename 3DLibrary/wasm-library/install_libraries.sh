
# Create lib folder
mkdir -p libraries/downloads



# ##################################### CGAL #####################################

CGAL_VERSION=5.5.2
CGAL_NAME=CGAL-5.5.2.tar.xz
CGAL_URL=https://github.com/CGAL/cgal/releases/download/v$CGAL_VERSION/$CGAL_NAME

echo "Downloading "$CGAL_NAME
wget -nc -q --show-progress -O libraries/downloads/$CGAL_NAME $CGAL_URL
echo "Extracting"
tar -xf libraries/downloads/$CGAL_NAME -C libraries
echo "Done"


# ##################################### BOOST #####################################

BOOST_VERSION=1.81.0
BOOST_NAME=boost_1_81_0.tar.gz
BOOST_URL=https://boostorg.jfrog.io/artifactory/main/release/$BOOST_VERSION/source/$BOOST_NAME

echo "Downloading "$BOOST_NAME
wget -nc -q --show-progress -O libraries/downloads/$BOOST_NAME $BOOST_URL
echo "Extracting"
tar -xf libraries/downloads/$BOOST_NAME -C libraries
echo "Done"


##################################### GMP #####################################

GMP_VERSION=6.2.1
GMP_NAME=gmp-$GMP_VERSION.tar.xz
GMP_URL=https://gmplib.org/download/gmp/$GMP_NAME

echo "Downloading "$GMP_NAME
wget -nc -q --show-progress -O libraries/downloads/$GMP_NAME $GMP_URL
echo "Extracting"
tar -xf libraries/downloads/$GMP_NAME -C libraries
echo "Done"


##################################### LIBIGL #####################################
LIBIGL_VERSION=2.4.0
LIBIGL_NAME=v$LIBIGL_VERSION.tar.gz
LIBIGL_URL=https://github.com/libigl/libigl/archive/refs/tags/$LIBIGL_NAME

echo "Downloading LIBIGL "$LIBIGL_NAME
wget -nc -q --show-progress -O libraries/downloads/LIBIGL$LIBIGL_NAME $LIBIGL_URL
echo "Extracting"
tar -xf libraries/downloads/LIBIGL$LIBIGL_NAME -C libraries
echo "Done"


##################################### EIGEN #####################################

EIGEN_VERSION=3.3.9
EIGEN_NAME=eigen-$EIGEN_VERSION.tar.bz2
EIGEN_URL=https://gitlab.com/libeigen/eigen/-/archive/$EIGEN_VERSION/$EIGEN_NAME

echo "Downloading "$EIGEN_NAME
wget -nc -q --show-progress -O libraries/downloads/$EIGEN_NAME $EIGEN_URL
echo "Extracting"
tar -xf libraries/downloads/$EIGEN_NAME -C libraries
echo "Done"

LIBIGL_VERSION=2.4.0
LIBIGL_NAME=v$LIBIGL_VERSION.tar.gz
LIBIGL_URL=https://github.com/libigl/libigl/archive/refs/tags/$LIBIGL_NAME

echo "Downloading LIBIGL "$LIBIGL_NAME
wget -nc -q --show-progress -O libraries/downloads/LIBIGL$LIBIGL_NAME $LIBIGL_URL
echo "Extracting"
tar -xf libraries/downloads/LIBIGL$LIBIGL_NAME -C libraries
echo "Done"


##################################### mpfr #####################################
MPFR_VERSION=4.2.0
MPFR_NAME=mpfr-$MPFR_VERSION.tar.xz
MPFR_URL=https://www.mpfr.org/mpfr-current/$MPFR_NAME

echo "Downloading "$MPFR_NAME
wget -nc -q --show-progress -O libraries/downloads/$MPFR_NAME $MPFR_URL
echo "Extracting"
tar -xf libraries/downloads/$MPFR_NAME -C libraries
echo "Done"