## Project description

The purpose of this project is to create a one-to-four player game<br>
inspired from the famous [r-type game](http://www.hardcoregaming101.net/r-type/) using a client/server architecture. This is important.<br>
It MUST be a client/server architecture.<br>
Peer-to-peer communication is not allowed.

## Dependencies

This project uses **conan**.
To install conan, checkout [conan documentation](https://docs.conan.io/en/1.7/installation.html)
or install it with **pip**:
>$ pip install conan

Then you need 3 remotes:

    - conan-center (installed with conan): https://bintray.com/conan/conan-center
    
    - epitech: https://bintray.com/epitech/public-conan
    
    - bincrafters: : https://bintray.com/bincrafters/public-conan 
    

You can install those by running the following commands:
>$ conan remote add conan-center https://api.bintray.com/conan/conan/conan-center 

>$ conan remote add epitech https://api.bintray.com/conan/epitech/public-conan

>$ conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan 

You can now build the **R-type project**

## Build

##### Linux
You MUST execute this command:
>$ mkdir build && cd build && conan install .. --build=missing && cmake .. -G “Unix Makefiles” && cmake --build .

#### Windows
You MUST execute this command:
>$ mkdir build && cd build && conan install .. --build=missing && cmake .. -G "Visual Studio 16 2019" && cmake --build .

Whether on a linux or windows system, the appropriate command will generate two binaries :

* r-type_client
* r_type_server

It will also generate you dynamic libraries which represents the enemies in the game.
You can find these libraries in the build/lib folder.

## Execute
The way to execute is the same in Linux and Windows system.
The only difference is that on Windows, a .sln solution will be generated.

You MUST first start by running the server
>$ cd build/bin && ./r-type_server

Once the server started, you can start one or several clients with :
>$ cd build/bin && ./r-type_client

## Use the server

How to use the server and what address and port it use.

#### Protocol

See the RFC

## Use the clients

How to use the client

## RFC additional documentation

You can find a detailed RFC documentation in the file 'docRFC.txt'

## Authors

This project has realized in Novemher 2020 by :
* Mathieu Schmerber
* Paul Surrans
* Cyprien Ricques
* Emilien Delevoye

*Epitech Lille - Promo 2023 students*

