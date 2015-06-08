exploot-server
==============

The Exploot MMO game server


## Dependencies
Google protobuf C library headers, you can install it on Arch Linux using ```pacman -S protobuf-c```

## Submodules
Clone repo and then run ```git submodule update --init``` to fetch latest version of exploot-protobuf.  
Then go to the ```submodules/exploot-protobuf``` folder and run ```build.sh```

## Dependencies
### Arch Linux
```bash
  pacman -S mysql-connector-c++ bullet enet
```

### Windows
Everything is versioned because it is hard to maintain. If you want to update libs I'll be happy to take your PR.

## MariaDB
You have to import SQL script located in ```sql``` folder inside your database. Then update your DB informations inside ```include/config.h```

## Compile
```bash
mkdir build
cd build
cmake ../.
make
```
