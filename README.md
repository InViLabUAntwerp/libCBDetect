# Libcbdetect

- Unofficial implemention of [libcbdetect](http://www.cvlibs.net/software/libcbdetect/) in C++ based
  on https://github.com/ftdlyc/libcbdetect.

Libdetect is fully automatic sub-pixel checkerboard / chessboard / deltille pattern detection. The algorithm
autmatically extracts corners to sub-pixel accuracy and combines them to (rectangular) checkerboards / chessboard-like.

---

# Development

## 0. Setting up Windows environment

- Install Visual Studio Build Tools:

    1. Download the "Visual Studio Build Tools" installer from
       Microsoft [(link)](https://aka.ms/vs/17/release/vs_BuildTools.exe)
    2. During installation, select "Desktop development with C++"

---

## 1. Installing local dependencies

### 1. OpenCV

1. **Windows (prebuilt binaries)**
    1. Download the latest Windows release ZIP from
       the [OpenCV GitHub releases page](https://github.com/opencv/opencv/releases).
    2. Extract it (e.g., to `C:\`).
    3. Set `OPENCV_DIR` in **System > Environment Variables** to the `C:\opencv\build`
       folder.  ([Integrating OpenCV with Visual Studio C++ Projects on Windows](https://christianjmills.com/posts/opencv-visual-studio-getting-started-tutorial/windows/?utm_source=chatgpt.com))

   > [!TIP]
   > Or use the following command in a PowerShell with administrator privileges to do everything at once
   > ```shell
   > $ver='4.11.0';$exe="$env:TEMP\opencv.exe";Invoke-WebRequest -Uri "https://github.com/opencv/opencv/releases/download/$ver/opencv-$ver-windows.exe" -OutFile $exe; Start-Process -FilePath $exe -ArgumentList "-y","-oC:\" -NoNewWindow -Wait; Remove-Item $exe; $base='C:\opencv'; $bin="$base\build\x64\vc16\bin"; $cfg="$base\build\x64\vc16\lib"; [Environment]::SetEnvironmentVariable('Path',[Environment]::GetEnvironmentVariable('Path','Machine')+';'+$bin,'Machine'); [Environment]::SetEnvironmentVariable('OpenCV_DIR',$cfg,'Machine'); $env:Path+=';'+$bin


2. **Linux (Ubuntu/Debian)**
   ```bash
   sudo apt update
   sudo apt install libopencv-dev -y
   ```  
   This installs both runtime and development headers/libraries for OpenCV
   4.x.  ([How to Install opencv in C++ on Linux?—GeeksforGeeks](https://www.geeksforgeeks.org/how-to-install-opencv-in-c-on-linux/?utm_source=chatgpt.com))

3. **macOS (Homebrew)**
   ```bash
   brew update
   brew install opencv
   ```  
   After installation, headers are in `/usr/local/include/opencv4`, libs in
   `/usr/local/lib`.  ([Getting started with Opencv with C++ - Nikhil Ramesh](https://nikku1234.github.io/2019-10-27-Getting-started-with-Opencv-with-C%2B%2B/?utm_source=chatgpt.com))

### 2. pybind11

1. **Windows**
   ```powershell
   pip install "pybind11[global]"
   ```

2. **Linux (Ubuntu/Debian)**
   ```bash
   sudo apt update
   sudo apt install -y python3-pybind11
   ```

3. **macOS (Homebrew)**
   ```bash
   brew install pybind11
   ```

---

## 2. Creating a Python virtual environment

> [!NOTE]
> This environment will be used for building the project.

### Linux & macOS (bash/zsh)

```bash
python3 -m venv .venv
source .venv/bin/activate
python -m pip install --upgrade pip wheel build pybind11 cibuildwheel
```

### Windows (PowerShell)

```powershell
py -3.10 -m venv .venv
.venv\Scripts\Activate.ps1
python -m pip install --upgrade pip wheel build pybind11 cibuildwheel
```

---

## 3. Building the package

### 3-a Local build

```bash
python -m build
```

`scikit-build-core` invokes **CMake + pybind11** to compile the C++ extension
for **your** Python, then packages:

```
dist/
  ├─ libCBDetect-0.1.0-cp313-cp313-macosx_15_0_arm64.whl
  └─ libCBDetect-0.1.0.tar.gz
```

**Windows only**: Repair the wheel with delvewheel to include all required DLLs:

```powershell
pip install delvewheel
$wheel = Get-ChildItem -Path .\dist\*.whl | Sort-Object LastWriteTime -Descending | Select-Object -First 1
delvewheel repair $wheel.FullName -w .\dist\repaired\
```

Install:

```bash
pip install dist/checkerboard-*.whl --force-reinstall
```

**Windows**: Use the repaired wheel:

```powershell
pip install dist\repaired\*.whl --force-reinstall
```

### 3-b Editable installation for rapid iteration

```bash
pip install -e .[dev]
```

Builds the extension **once** and leaves the Python
files linked to your working copy, so every code change is picked up
immediately.

---

### Tips

If using CLion (on Windows), change the default toolchain in the CMake Profiles to ***Visual Studio***.

---

### Original CPP code:

https://github.com/ftdlyc/libcbdetect

### Reference Papers

[1] Geiger, A., Moosmann, F., Car, Ã–., & Schuster, B. (2012, May). Automatic camera and range sensor calibration using
a single shot. In Robotics and Automation (ICRA), 2012 IEEE International Conference on (pp. 3936-3943). IEEE.  
[2] SchÃ¶nbein, M., StrauÃŸ, T., & Geiger, A. (2014, May). Calibrating and centering quasi-central catadioptric cameras.
In Robotics and Automation (ICRA), 2014 IEEE International Conference on (pp. 4443-4450). IEEE.  
[3] Placht, S., FÃ¼rsattel, P., Mengue, E. A., Hofmann, H., Schaller, C., Balda, M., & Angelopoulou, E. (2014,
September). Rochade: Robust checkerboard advanced detection for camera calibration. In European Conference on Computer
Vision (pp. 766-779). Springer, Cham.  
[4] Ha, H., Perdoch, M., Alismail, H., Kweon, I. S., & Sheikh, Y. (2017, October). Deltille Grids for Geometric Camera
Calibration. In 2017 IEEE International Conference on Computer Vision (ICCV) (pp. 5354-5362). IEEE.  
[5] Duda, A., & Frese, U. (2018, September). Accurate Detection and Localization of Checkerboard Corners for
Calibration. In British Machine Vision Conference (BMCV), 2018.  
[6] Sels, S., Ribbens, B., Vanlanduit, S., & Penne, R. (2019). Camera Calibration Using Gray Code. In Sensors (Vol. 19,
Issue 2, p. 246). MDPI AG. https://doi.org/10.3390/s19020246
[7] Hillen, M., De Boi, I., De Kerf, T., Sels, S., Cardenas De La Hoz, E., Gladines, J., Steenackers, G., Penne, R., & Vanlanduit, S. (2023). Enhanced Checkerboard Detection Using Gaussian Processes. Mathematics, 11(22), 4568. https://doi.org/10.3390/math11224568
