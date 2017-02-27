# skanlite
This is a SkanLite fork with D-Bus interface support. Main purpose - control SkanLite with global hotkeys

I've changed its version to **2.0.2 (fork with D-Bus)** to avoid misunderstanding.

## Why I need D-Bus?
From time to time I'm scanning big fat books with my simple HP 4370. And I think out many improvements that could make 
this work a bit easier. My biggest wish was to make SkanLite work with my scanner hardware buttons (didn't work for my HP).
And fix few other annoying problems. At the end I pulled SkanLite sources and tried to do something. And realized following:
* SkanLite basically is a fin wrapper around ***KSaneIface::KSaneWidget*** - a control which is not a part of SkanLite
project. I mean when you launch SkanLite all you see on screen except 4 buttons at very bottom - isn't a SkanLite at all.
It's KSaneWidget from ***libksane*** shared library. SkanLite is a few dialogs with settings and filename selection
around
this widget. Which means to fix many UI and UX things you must patch libksane project and perhaps then you'll need to
patch SkanLite as KSaneWidget interface is quite limited.
* KSaneWidget **does** react on scanner's hardware buttons!!! Most probably you may see a list of checkboxes named
"Scanner button X" at second tab. They are disabled but they are real. They are automatically created based on button
titles
KSaneWidget receives. Moreover - if you press (or press and hold) your hardware buttons you'll find that corresponding
checkboxes get on/off state. These are just indicators to demonstrate what hw buttons were found and how they work.
Even better - KSaneWidget does inform outer world about this activity and SkanLite receives these signals! It just do
nothing except printing something like "Scanner Button 0 pressed" to the console!!! I was quite surprise 
to found out that SkanLite has all it needs to support hw buttons but it doesn't. At first I decided that scanners do
not provide meaningful names for buttons (which is true) and authors just didn't know how process these events, so I
can just let user decide which action (scan for example) to assign to which button and that's it!
Well, hopefully soon I understood that the reason was different - hw buttons work was just unstable. For example, for
my HP 4370 they work perfectly
just until you scan something first time. After that KSaneWidget lost its ability to hear hw button clicks. And I'm
99% sure - its a driver problem.
It's one of many problems with my scanner which roots are in binary driver. And my driver is a part of quite big 
collection of drivers from **sane-backends**. In fact my device share one driver with 
several HP models and driver has "basic" quality level according to 
[SANE](sane-project.org/sane-mfgs.html#Z-HEWLETT-PACKARD). And I don't think it's going to be improved anytime soon. 
And I have no time to debug drivers. If you are here that means your device driver sucks too. And together with generic
button names problem this makes generic implementation of hardware buttons support not feasible. But I left one trick
for you to try.
* KSaneWidget and most probably SANE by nature require exclusive access to device. In my case buggy driver makes
KSaneWidget useless just after it lost access to it once. No any refreshes help. You just need to recreate widget 
from scratch. Thus I seriously doubt SkanLite can work with **scanbd**. It either crash when widget lost exclusive 
access to device or buggy driver will stop send hw buttons info after the first scan as I'm sure same driver is into 
play as no other exists.

Considering all above I give up with HW buttons and decided to automatize SkanLite at least with global hotkeys. And 
that works. Most probably you should give up with hw buttons too but I'll leave a way and instructions on how you 
still can easily try to use hw buttons with your device. If you're luckier with drivers for your model - it can work.

## How I want enhance SkanLite UX with D-Bus?
* I need a **hotkey to start/cancel scanning**. As my device is slow I'm usually minimize SkanLite as possible and 
moving it out of desktop boundaries leaving only scan button visible. I make its window
always on screen via DE window menu and can watch a movie just turning pages and clicking Enter from time to time. 
I believe it's a good payload for watching movies, but I can't watch them fullscreen. I also must be sure button has 
focus. Binding scan with global hotkey let me keep SkanLite at background and watch youtube fullscreen.
* I'm scanning pages in 300 dpi and 600 dpi for photos. I'm doing this in grayscale and color if needed. And I'm 
switching off shadows autocorrection for color mode as I'm getting some color stripes on images sometimes and turning
back this option for grayscale. So I'm using 4 different modes for scanning and sometimes settings are on different 
tabs. Currently I got a large amount of work where I should switch every few pages. That's tiresomely. So I need a
**hotkeys to switch between different scanner's settings profiles**.
* Sometimes I need to scan something asap and can focus on that activity. Even scanning in 300 dpi is slow enough
on my HP to let me turn the page before mechanism return to start position again. With saving images without preview 
I can literally keep scanning without stop if only SkanLite had this feature. Currently you have to turn to PC every
time after scan to press something. With D-Bus and **a small script** I can make SkanLite **scan again and again
without stop and any user action**. And if I got a few bad or even empty images bcs I wasn't fast enough - I'll 
filter them out later.
* **HW Buttons support**. If you are lucky you can check out if your driver is good enough to reliable pass button
events to SkanLite. Just go to parameters and check very last checkboxes. Below "Save debugging images". If there
are some - these are buttons KSaneWidget "see" and their names. When try to press buttons or hold them to find out 
if they work and which one corresponds to which title. Checkboxes should change their on/off state. If they work 
try to scan something or your other regular stuff to ensure they keep working. If it's so - you're lucky. As SkanLite
"knows" about these events (just don't process them) - I'll signal them via D-Bus. All you need is a script which 
looks for a D-Bus signal, check button title and call scan method back from SkanLite. This'll let you scan, cancel 
scanning, switch settings profiles with hw buttons. Perhaps I'll implement this based on optional setting file content
later but D-Bus based script is more flexible.

## What is done?

* **Keyboard hotkeys to start/cancel scanning**

* **Keyboard hotkeys to switch between different scanner's settings profiles**  

Two above could be imported into Plasma's KHotKeys to automatically predefine hotkeys for two tasks above. Settings file is in hotkeys_and_scripts.

* **script for endless scanning without UI interaction**

* **script for HW Buttons support**  

One more time - if only your device driver works as expected. Technically it can be done without D-Bus and scripts, but I'm ok with current approach.

* **some minor UI bugfixes**  

Fixed directory selection dialog, file naming in case of empty prefix.
