#!/bin/bash

# 1. Enter the build directory
cd ~/AOS-manifest/build

# 2. Recompile (stops if there is an error)
echo "--- Building ---"
ninja
if [ $? -ne 0 ]; then
    echo "Build failed! Fix errors first."
    exit 1
fi

# 3. Copy image to TFTP server
echo "--- Deploying to TFTP ---"
cp images/sos-image-arm-odroidc2 /srv/tftp/

# 4. Notify
echo "--- Success! ---"
echo "Reboot your Odroid now (run 'run bootcmd' or 'reset' in UART)."
