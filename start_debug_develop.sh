#!/usr/bin/sh


echo "Develop version started. Client is accessible on: http://localhost:81"
sudo FW_ENV=dev gdb ./develop/build/forradia-world
