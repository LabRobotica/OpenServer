# OpenServer - The backend server for CRCOpen for Comau Robots

This program allows you to process information outside the LPC, as it may lack processing power for certain applications, and send it to it to relay the CRC securely.


## To install

First clone the repository on LPC:

    git clone https://github.com/LabRobotica/OpenServer.git

Now go to the folder and create a folder for the build files:

    cd OpenServer && mkdir build && cd build

Now whenever you need to complete and execute run the command below:

    cmake .. && make && clear && sudo ./OpenServer

Or separate/modify the commands according to your needs.
