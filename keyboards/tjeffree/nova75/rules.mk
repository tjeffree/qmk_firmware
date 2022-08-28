# MCU name
MCU = RP2040
BOOTLOADER = rp2040
PICO_INTRINSICS_ENABLED = no

BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
COMBO_ENABLE = yes          # Combos enabled

AUDIO_SUPPORTED = no        # Audio is not supported
RGB_MATRIX_SUPPORTED = no   # RGB matrix is supported and enabled by default
RGBLIGHT_SUPPORTED = no     # RGB underglow is supported, but not enabled by default
RGB_MATRIX_ENABLE = no      # Enable keyboard RGB matrix functionality

LAYOUTS = ortho_5x15

PICO_INTRINSICS_ENABLED = no
