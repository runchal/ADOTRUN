1. You need to install Anaconda Python 3.6

2. Go to your Terminal and type `conda` just to confirm it’s installed.

3. Create a new environment. Say you want to call it `artenv` then you type: `conda create -n artenv python=3.5`

4. Enter your environment. `source activate artenv`. Your Terminal prompt should now begin with `(artenv)`

5. You will need to do step 4 every time you open a new Terminal window. This ensures you’re in the right environment.

6. You’ll need to install OpenCV (for Python). Do it this way: `conda install -c menpo opencv3`. Make sure it didn’t explicitly fail.
  6*. There may be an error here if you try to intall `opencv` if you have a conflicting version.

7. Install dlib: `conda install -c menpo dlib`. Make sure it didn’t explicitly fail.

8. Install the other necessary Python packages. Beware of fail messages (“Already installed” messages are ok). In general, you can answer "y" to any prompts
`conda install -c anaconda numpy`
`conda install -c anaconda pandas`
`conda install -c anaconda scipy`
`conda install scikit-learn`
`conda install scikit-image`

9. You need to temporarily exit your environment. `source deactivate artenv`. Make sure your Terminal prompt no longer begins with `(artenv)`.

10. Use the following three commands to install Torch:
A. `git clone https://github.com/torch/distro.git ~/torch --recursive`
B. `cd ~/torch; bash install-deps;`
C. `./install.sh`
  10* You may get an error here and need to edit your bash profile and add: `. /Users/[USERNAME]/torch/install/bin/torch-activate`

11. Refresh your profile by doing `source ~/.bash_profile`

12. Torch should work. Test it by entering `th` on your Terminal. Exit Torch by pressing `Ctrl+C` twice.

13. Install packages using this command: `for NAME in dpnn nn optim optnet csvigo cutorch cunn fblualib torchx tds; do luarocks install $NAME; done`

14. Make sure you’re at your user root directory: `cd ~`

15. Enter again your environment `source activate artenv`

16. Clone OpenFace: `git clone https://github.com/cmusatyalab/openface.git ~/openface`

17. Enter the OpenFace directory `cd openface` and install it `sudo python setup.py install` (you may need to enter your Mac password)

18. In the openface folder you have a folder called models. You need to download the ML models there. Ask me how. There’s a script but it doesn’t work properly. You need to add the models in `https://www.dropbox.com/s/toaiiqkh1htmir0/openface.zip?dl=0` to `/openface/models/openface/`.

19. In `/openface/demos` open `classifier.py` and replace the `from sklearn.lda import LDA` line from classifier.py with this: `from sklearn.discriminant_analysis import LinearDiscriminantAnalysis as LDA`

20. Once this is done, you can test `python classifier.py infer models/openface/celeb-classifier.nn4.small2.v1.pkl ./images/examples/carell.jpg` in `/openface/demos/`

21. Almost done. You just need get the Python script from me. Replace your local IP into the code and run it after launching the app :)
