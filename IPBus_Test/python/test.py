import uhal

manager = uhal.ConnectionManager("file://xml/connections.xml")
hw = manager.getDevice("hcal.crate115.slot1")

print hw

fw_ver = hw.getNode("FW_VER").read()
const0 = hw.getNode("CONST0").read()
const1 = hw.getNode("CONST1").read()

hw.dispatch()

print "Firmware Version: ", fw_ver
print "Constant 0: ", hex(const0)
print "Constant 1: ", hex(const1)
