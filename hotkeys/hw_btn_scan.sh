#!/bin/bash

# this script listens for D-Bus buttonPressed signal from SkanLite
# checks which button is pressed (default: Button 0)
# and sends D-Bus command 'scan' to SkanLite

# WARNING: buttonPressed might workunstable bcs of bad driver
# WARNING: for example my HP 4370 stop sending hw btn events just after first scan

interface=org.kde.skanlite
sender=org.kde.skanlite
member=buttonPressed
command=scan

# listen for buttonPressed DBus events,
# each time we enter the loop, we just got an event
# so handle the event, e.g. by checking button name and its state.

dbus-monitor --profile "type='signal',sender='$sender',interface='$interface',member='$member'" --monitor |
while read -r line; do    
# uncomment the line below to output to console all incoming text 
# this may be useful to detect proper button names
# printf "Received line: $line\n"
    
  if [[ $line == *"button 0"* ]]; then
   read -r line;
   if [[ $line == *"Scanner button 0"* ]]; then
    read -r line;
     if [[ $line == *"boolean true"* ]]; then
      #printf "\nButton pressed. Performing scan.\n"
      dbus-send --session --dest=$interface --type=method_call  / $interface.$command
     fi
   fi
  fi
done
