#!/bin/bash

device=$1

./JLink/JLinkGDBServerCLExe -device $1 -if swd -speed auto -ir

