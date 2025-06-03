define start_pico
  target extended-remote:3333
  file RP2040_GB.elf
  monitor reset init
  monitor load
  monitor reset
end
