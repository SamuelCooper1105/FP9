data_file = "~/home/pi/Team9/output.txt"

def auto_convert(value):
    value = value.strip()
    try:
        num = float(value)
        return int(num) if num.is_integer() else num
    except ValueError:
        return value

def read_from_output_file():
    unmasked_data = {}
    with open(data_file, "r") as f:
        for line in f:
            if ":" not in line:
                continue
            key, value = line.split(":", 1)
            unmasked_data[key.strip()] = auto_convert(value)
    return unmasked_data

def get_car_data():
    try:
        data = read_from_output_file()
    except:
        return {}

    return {
            "rpm": data.get("RPM", 0),
            "coolant_temp": data.get("COOLANT_TEMP", 0),
            "speed": data.get("MPH", 0),
            "throttle": data.get("THROTTLE_POS", 0),
            "o2_mv": data.get("OXYGEN_SENSOR", 0),
            "mat_temp": data.get("MAT_SENS", 0),

            "iac_steps": data.get("step_count", 0),
            "egr_duty": data.get("EGR_duty_cycle", 0),
            "blm": data.get("BLM", 0),

            "overdrive": data.get("OVERDRIVE", 0),
            "shift_light": data.get("shigt_light", 0),
            "closed_loop": data.get("CLOSED_LOOPF", 0),
            "rich_lean": data.get("RICH_LEANF", 0),
            }
