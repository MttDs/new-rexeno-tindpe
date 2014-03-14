#! /bin/sh


AnalogFunc=/usr/sbin/analogy_config
DeviceNode=analogy0
DeviceDriver=analogy_ni_pcimio
#DeviceDriver=analogy_8255
PCIBus=`lspci | grep "National Instruments" | cut -c2`
PCISlot=`lspci | grep "National Instruments" | cut -c5`
DeviceSlots="0x$PCIBus","$PCISlot "

echo $AnalogFunc "$DeviceNode $DeviceDriver $DeviceSlots" 
sudo $AnalogFunc $DeviceNode $DeviceDriver $DeviceSlots
