from flask import Flask, render_template, jsonify, request, redirect, session
from aldl_reader import get_car_data
from database import setup_database, save_car_data, get_recent_data, get_trip_summary

app = Flask(__name__)
app.secret_key = "my_secret_key"

def add_metrics(data):
    rpm = data.get("RPM", 0) or 0
    throttle = data.get("TPS_V", 0) or 0
    battery = data.get("battery", 12.6) or 12.6
    coolant = data.get("COOLANT_F", 0) or 0

    engine_load = (throttle * 20) + (rpm / 3000 * 30)

    if engine_load > 100:
        engine_load = 100

    data["engine_load"] = round(engine_load, 1)
    data["battery"] = battery

    if battery >= 13.5:
        data["battery_health"] = "Charging"
    elif battery >= 12.2:
        data["battery_health"] = "Okay"
    else:
        data["battery_health"] = "Low"

    if coolant < 170:
        data["coolant_status"] = "Warming Up"
    elif coolant <= 210:
        data["coolant_status"] = "Normal"
    else:
        data["coolant_status"] = "Hot"

    return data

@app.route("/", methods=["GET", "POST"])
def login():
    error = None
    if request.method == "POST":
        username = request.form["username"]
        password = request.form["password"]

        if username == "admin" and password == "project525":
            session["logged_in"] = True
            return redirect("/dashboard")
        else:
            error = "Wrong username or password"

    return render_template("login.html", error=error)

@app.route("/dashboard")
def dashboard():
    if not session.get("logged_in"):
        return redirect("/")

    data = add_metrics(get_car_data())
    return render_template("dashboard.html", data=data)

@app.route("/data")
def data():
    if not session.get("logged_in"):
        return jsonify({"error": "not logged in"})

    car_data = add_metrics(get_car_data())
    save_car_data(car_data)
    return jsonify(car_data)

@app.route("/logs")
def logs():
    if not session.get("logged_in"):
        return redirect("/")

    rows = get_recent_data()
    return render_template("logs.html", rows=rows)

@app.route("/summary")
def summary():
    if not session.get("logged_in"):
        return redirect("/")

    trip_summary = get_trip_summary()
    return render_template("summary.html", summary=trip_summary)

@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")

if __name__ == "__main__":
    setup_database()
    app.run(host="0.0.0.0", port=5000, debug=False)
    
    
    
    
