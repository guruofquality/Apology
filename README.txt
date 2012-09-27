########################################################################
## Apology - An Actor Topology
########################################################################

------------------------------------------------------------------------
-- Prerequisites
------------------------------------------------------------------------
* C++ compiler (gcc and MSVC tested)
* CMake
* Boost - boost headers, and the thread library

------------------------------------------------------------------------
-- Get the source code
------------------------------------------------------------------------
git clone https://github.com/guruofquality/Apology.git
cd Apology
git submodule init
git submodule update

------------------------------------------------------------------------
-- Installation instructions
------------------------------------------------------------------------
mkdir <build dir>
cd <build dir>
cmake <source dir>
make
sudo make install
