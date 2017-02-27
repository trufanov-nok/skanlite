In this folder you can find some sample shell scripts and setting files.

**skanlite.khotkeys** - is a settings file which can be imported in KHotKeys application. KHotKeys is part of the KDE Plasma
desktop that manages keyboard shortcuts and mouse gestures to control applications, run specific commands, etc. Launch it,
import skanlite.khotkeys file and this will create a new category of keyboard shortcuts automatically enabled in your system. The shortcuts include:
* Alt+S to start scanning
* Alt+C to cancel scanning if performed
* Ctrl+Alt+*N* to save current SkanLite scanner settings as Profile *N*.
Alt+*N* to restore SkanLite scanner settings from Profile N. Restore default settings if there is no such profile.
Where *N* is from 1 to 4. Profiles are scanner model specific. You can easily create any number of profiles and rebind them to other keys if needed.


**hw_btn_scan.sh** - bash script that listens for D-Bus signals emitted by SkanLite and sends scan command on reception.
By default it waits for buttonClick signal with button text "Button 0" and pressed state. You can adjust this for your scanner's button.
You can uncomment one line in script to output details about all buttons signals and choose right name and state.

**endless_scan.sh** - once launched sends scan command to SkanLite and wait for end of scan operation. Then repeat these steps endlessly.
That mean your scanner might scan and save images without stops and asap if you disable scan preview and choose autosave in SkanLite settings.
