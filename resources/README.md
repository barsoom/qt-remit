## Regenerate icon files
App icons can  be regenerated starting from the files inside this folder. 

If on Mac, you can use the following:

```
# Make sure you have imagemagick installed, e.g.:
brew install imagemagick

# For Windows:
magick assets/icon.iconset/icon_16.png assets/icon.iconset/icon_32.png assets/icon.iconset/icon_48.png assets/icon.iconset/icon_64.png assets/icon.iconset/icon_128.png assets/icon.iconset/icon_256.png qt-remit.ico

# For Mac:
iconutil -c icns assets/icon.iconset -o qt-remit.icns # Mac icons
```

On a Linux system you can try achieving the same using packages like: `imagemagick` and `png2icns`.
