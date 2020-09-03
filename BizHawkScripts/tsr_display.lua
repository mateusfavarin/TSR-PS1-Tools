local X_POS = 0x0C0A38
local Y_POS = 0x0C0A3C
local Z_POS = 0x0C0A40
local X_SPEED = 0x0C0A8E
local Y_SPEED = 0x0C0A90
local Z_SPEED = 0x0C0A92
local ANGLE = 0x0C0A8A

local x, y, z, ver_spd, hor_spd, angle

local XTEXT = 2

while true do

    x = memory.read_s32_le(X_POS) * -1
    y = memory.read_s32_le(Y_POS) * -1
    z = memory.read_s32_le(Z_POS) * -1

    --  Angle value range is [0, 4095]
    angle = memory.read_u16_le(ANGLE)
    -- Converting angle to degrees in range [0, 180]
    if (angle > 2048) then
        angle = (angle * -1 % 2048)
    end
    angle = string.format("%.2f", (angle * 180 / 2048) - 90)

    ver_spd = memory.read_s16_le(Y_SPEED) * -1
    -- Horizontal speed is the hypotenuse of a right angle triangle with X_SPEED and Z_SPEED as its sides
    hor_spd = string.format("%.2f", math.sqrt(memory.read_s16_le(X_SPEED)^2 + memory.read_s16_le(Z_SPEED)^2))

    gui.text(XTEXT, 40, "X : " .. x, "white")
    gui.text(XTEXT, 60, "Z : " .. z, "white")
    gui.text(XTEXT, 80, "Y : " .. y, "white")
    gui.text(XTEXT, 100, "Angle : " .. angle, "white")
    gui.text(XTEXT, 140, "Ver Speed : " .. ver_spd, "white")
    gui.text(XTEXT, 160, "Hor Speed : " .. hor_spd, "white")

    emu.frameadvance()
end