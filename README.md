# OpenServer - The backend server for CRCOpen for Comau Robots

This program allows you to process information outside the LPC, as it may lack processing power for certain applications, and send it to it to relay the CRC securely.

## Pandemic Version

This version does not use the CRCOpen library to be able to be compiled outside the LPC, to work in home office.

### To install

First clone the repository on LPC:

    git clone https://github.com/LabRobotica/OpenServer.git

Now go to the folder and create a folder for the build files:

    cd OpenServer && mkdir build && cd build

Now whenever you need to compile and execute, just run the command below:

    cmake .. && make && clear && sudo ./OpenServer

Or separate/modify the commands according to your needs.
