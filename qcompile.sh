#!/bin/csh -f

if ($#argv != 2) then
	echo "usage: qcompile teamname {east|west}, teamname plays {east|west} side"
	exit 1
endif

echo "qcompile: Removing old stuff"
rm -f *.a
rm -f soccer
rm -f core

if ($1 == "deepq") then
	echo "Don't play deepq against itself. Exiting..."
	echo ""
	exit 1
endif

if ($2 == "east") then
	echo "qcompile: Team "{$1}" playing east"
	echo "qcompile: Moving to ./teams/"{$1}" ."
	echo "qcompile: Compiling libraries for the " {$1} " team."
	cd teams/{$1}
	make libeast.a
	cp libeast.a ../..
	make libcommon.a
	cp libcommon.a ../../libeastcommon.a

	echo "qcompile: Team deepq playing west"
	cd ../deepq
	make libwest.a
	cp libwest.a ../..
	make libcommon.a
	cp libcommon.a ../../libwestcommon.a
else
	echo "qcompile: Team "{$1}" playing west"
	echo "qcompile: Moving to ./teams/"{$1}" ."
	echo "qcompile: Compiling libraries for the " {$1} " team."
	cd teams/{$1}
	make libwest.a
	cp libwest.a ../..
	make libcommon.a
	cp libcommon.a ../../libwestcommon.a
	
	echo "qcompile: Team deepq playing east"
	cd ../deepq
	make libeast.a
	cp libeast.a ../..
	make libcommon.a
	cp libcommon.a ../../libeastcommon.a
endif

cd ../..
echo "qcompile: Compiling and linking soccer."
make soccer

