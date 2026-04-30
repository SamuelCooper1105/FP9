import sqlite3
from datetime import datetime

DB_NAME = "telematics.db"

def setup_database():
    connection = sqlite3.connect(DB_NAME)
    cursor = connection.cursor()

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS car_data (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            time TEXT,

            -- core data
            rpm INTEGER,
            coolant_temp REAL,
            speed INTEGER,
            throttle REAL,
            o2_mv REAL,
            mat_temp REAL,

            -- engine / control
            iac_steps INTEGER,
            egr_duty REAL,
            bpclc INTEGER,
            blm INTEGER,
            airflow_raw INTEGER,
            injector_bpw_raw INTEGER,

            -- flags
            overdrive INTEGER,
            shift_light INTEGER,
            high_battery INTEGER,
            aldl_mode INTEGER,
            diag_position INTEGER,

            -- system info
            prom_id_a TEXT,
            prom_id_b TEXT,
            malf_word_1 TEXT,
            malf_word_2 TEXT,
            malf_word_3 TEXT,
            malf_word_4 TEXT,
            air_fuel_mode TEXT,
            mcu_input_status TEXT,

            oldpa3 INTEGER,
            aldl_change_counter INTEGER,

            raw_frame TEXT,

            battery_health TEXT,
            coolant_status TEXT
        )
    """)

    connection.commit()
    connection.close()


def save_car_data(data):
    connection = sqlite3.connect(DB_NAME)
    cursor = connection.cursor()

    cursor.execute("""
        INSERT INTO car_data (
            time,
            rpm,
            coolant_temp,
            speed,
            throttle,
            o2_mv,
            mat_temp,
            iac_steps,
            egr_duty,
            bpclc,
            blm,
            airflow_raw,
            injector_bpw_raw,
            overdrive,
            shift_light,
            high_battery,
            aldl_mode,
            diag_position,
            prom_id_a,
            prom_id_b,
            malf_word_1,
            malf_word_2,
            malf_word_3,
            malf_word_4,
            air_fuel_mode,
            mcu_input_status,
            oldpa3,
            aldl_change_counter,
            raw_frame,
            battery_health,
            coolant_status
        )
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    """, (
        datetime.now().strftime("%Y-%m-%d %H:%M:%S"),
        data.get("RPM"),
        data.get("COOLANT_F"),
        data.get("MPH"),
        data.get("TPS_V"),
        data.get("O2_MV"),
        data.get("MAT_F"),
        data.get("IAC_STEPS"),
        data.get("EGR_DUTY"),
        data.get("BPCLC"),
        data.get("BLM"),
        data.get("AIRFLOW_RAW"),
        data.get("INJECTOR_BPW_RAW"),
        data.get("OVERDRIVE"),
        data.get("SHIFT_LIGHT"),
        data.get("HIGH_BATTERY"),
        data.get("ALDL_MODE"),
        data.get("DIAG_POSITION"),
        data.get("PROM_ID_A"),
        data.get("PROM_ID_B"),
        data.get("MALF_WORD_1"),
        data.get("MALF_WORD_2"),
        data.get("MALF_WORD_3"),
        data.get("MALF_WORD_4"),
        data.get("AIR_FUEL_MODE"),
        data.get("MCU_INPUT_STATUS"),
        data.get("OLDPA3"),
        data.get("ALDL_CHANGE_COUNTER"),
        data.get("RAW_FRAME"),
        data.get("battery_health"),
        data.get("coolant_status")
    ))

    connection.commit()
    connection.close()


def get_recent_data():
    connection = sqlite3.connect(DB_NAME)
    connection.row_factory = sqlite3.Row
    cursor = connection.cursor()

    cursor.execute("""
        SELECT * FROM car_data
        ORDER BY id DESC
        LIMIT 20
    """)

    rows = cursor.fetchall()
    connection.close()
    return rows


def get_trip_summary():
    connection = sqlite3.connect(DB_NAME)
    cursor = connection.cursor()

    cursor.execute("""
        SELECT
            COUNT(*) as total_records,
            ROUND(AVG(rpm), 1) as average_rpm,
            MAX(rpm) as max_rpm,
            MAX(coolant_temp) as max_coolant,
            ROUND(AVG(coolant_temp), 1) as average_coolant,
            MAX(speed) as max_speed,
            ROUND(AVG(throttle), 2) as average_throttle,
            ROUND(AVG(o2_mv), 1) as average_o2,
            ROUND(AVG(mat_temp), 1) as average_mat,
            ROUND(AVG(egr_duty), 1) as average_egr
        FROM car_data
    """)

    summary = cursor.fetchone()
    connection.close()
    return summary