#!/usr/bin/env sh

mute() {
  pamixer --toggle-mute
  
  if [ "$(pamixer --get-mute)" = true ]; then 
    notify-send -h string:x-canonical-private-synchronous:sys-notify "Muted"
  else 
    notify-send -h string:x-canonical-private-synchronous:sys-notify "Unmuted"
  fi

  kill -42 $(pidof dwmblocks)
  exit
}

case $1 in 
  i) pamixer -i 5 ;; 
  d) pamixer -d 5 ;;
  m) mute ;; 
  *) echo "Invalid Option" ;;
esac

notify-send -h string:x-canonical-private-synchronous:sys-notify "Volume:" "$(pamixer --get-volume)"
kill -42 $(pidof dwmblocks)
