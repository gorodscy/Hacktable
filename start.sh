#!/bin/sh
echo "Starting a Pd to camera capture patch..."
pd-extended camera.pd &
echo "Starting another Pd to audio synth patch..."
pd-extended -rt -path vendor/DIY2/ sintetizador2.pd &
