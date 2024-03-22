try:
    import serial

    print("Serial module found!")
except ImportError:
    print("Serial module not found!")
