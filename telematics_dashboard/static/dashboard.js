function setText(id, value, suffix = "") {
    const el = document.getElementById(id);
    if (el) el.textContent = (value ?? "--") + suffix;
}

function flag(value) {
    return Number(value) ? "On" : "Off";
}

function updateDashboard() {
    fetch("/data")
        .then(response => response.json())
        .then(data => {
            setText("raw_frame", data.RAW_FRAME);

            setText("rpm", data.RPM);
            setText("coolant", data.COOLANT_F, " °F");
            setText("speed", data.MPH, " MPH");
            setText("tps", data.TPS_V, " V");
            setText("o2", data.O2_MV, " mV");
            setText("mat", data.MAT_F, " °F");
            setText("iac", data.IAC_STEPS);
            setText("egr", data.EGR_DUTY, "%");
            setText("bpclc", data.BPCLC);
            setText("blm", data.BLM);
            setText("aldl_change_counter", data.ALDL_CHANGE_COUNTER);

            setText("prom_id_a", data.PROM_ID_A);
            setText("prom_id_b", data.PROM_ID_B);

            setText("malf_word_1", data.MALF_WORD_1);
            setText("malf_word_2", data.MALF_WORD_2);
            setText("malf_word_3", data.MALF_WORD_3);
            setText("malf_word_4", data.MALF_WORD_4);
            setText("air_fuel_mode", data.AIR_FUEL_MODE);
            setText("mcu_input_status", data.MCU_INPUT_STATUS);

            setText("oldpa3", data.OLDPA3);
            setText("airflow_raw", data.AIRFLOW_RAW);
            setText("injector_bpw_raw", data.INJECTOR_BPW_RAW);

            setText("overdrive", flag(data.OVERDRIVE));
            setText("malf_14_15", flag(data.MALF_14_15));
            setText("ref_pulse", flag(data.REF_PULSE));
            setText("aldl_mode", flag(data.ALDL_MODE));
            setText("diag_position", flag(data.DIAG_POSITION));
            setText("aldl_position", flag(data.ALDL_POSITION));
            setText("high_battery", flag(data.HIGH_BATTERY));
            setText("shift_light", flag(data.SHIFT_LIGHT));
        })
        .catch(err => console.log("Data fetch error:", err));
}

setInterval(updateDashboard, 1000);
updateDashboard();