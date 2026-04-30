import os

data_file = os.path.join(os.path.dirname(__file__), "output.txt")

def auto_convert(value):
    value = value.strip()
    try:
        num = float(value)
        return int(num) if num.is_integer() else num
    except ValueError:
        return value

def read_from_output_file():
    data = {}

    try:
        with open(data_file, "r") as f:
            for line in f:
                if ":" not in line:
                    continue

                key, value = line.split(":", 1)
                data[key.strip()] = auto_convert(value)

    except FileNotFoundError:
        return {}

    return data

def get_car_data():
    data = read_from_output_file()

    return {
        "RPM": data.get("RPM", 0),
        "COOLANT_F": data.get("COOLANT_TEMP", 0),
        "MPH": data.get("MPH", 0),
        "TPS_V": data.get("THROTTLE_POS", 0),
        "O2_MV": data.get("OXYGEN_SENSOR", 0),
        "MAT_F": data.get("Temp", 0),

        "IAC_STEPS": data.get("step_count", 0),
        "EGR_DUTY": data.get("EGR_duty_cycle", 0),
        "BPCLC": data.get("BPCLC", 0),
        "BLM": data.get("BLM", 0),
        "ALDL_CHANGE_COUNTER": data.get("ALDL_CHANGE_COUNTER", 0),

        "OVERDRIVE": data.get("OVERDRIVE", 0),
        "MALF_14_15": data.get("MALF", 0),
        "REF_PULSE": data.get("ref_pulse", 0),
        "ALDL_MODE": data.get("ALDL_mode", 0),
        "DIAG_POSITION": data.get("dia_pos", 0),
        "ALDL_POSITION": data.get("aldl_pos", 0),
        "HIGH_BATTERY": data.get("high_bat_volt", 0),
        "SHIFT_LIGHT": data.get("shigt_light", 0),

        "PROM_ID_A": data.get("PROMID_ONE", "--"),
        "PROM_ID_B": data.get("PROMID_TWO", "--"),

        "CLOSED_LOOPF": data.get("CLOSED_LOOPF", 0),
        "RICH_LEANF": data.get("RICH_LEANF", 0),

        "PARK_NET": data.get("PARK_NET", 0),
        "NOT_THIRD": data.get("NOT_THIRD", 0),
        "TCC_LOCKED": data.get("TCC_LOCKED", 0),
        "FAN_REQ": data.get("FAN_REQ", 0),
        "AC_REQ": data.get("AC_REQ", 0),
    }