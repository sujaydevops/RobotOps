const robots = [
    { id: "RBT-001", battery: 98, temperature: 36.2, speed: 1.2, status: "ONLINE" },
    { id: "RBT-002", battery: 91, temperature: 38.5, speed: 0.8, status: "ONLINE" },
    { id: "RBT-003", battery: 87, temperature: 40.1, speed: 1.5, status: "ONLINE" },
    { id: "RBT-004", battery: 79, temperature: 42.3, speed: 0.6, status: "ONLINE" },
    { id: "RBT-005", battery: 95, temperature: 35.8, speed: 1.1, status: "ONLINE" }
];

function determineStatus(robot) {
    if (robot.battery < 20 || robot.temperature > 55) {
        return "CRITICAL";
    }

    if (robot.battery < 40 || robot.temperature > 48) {
        return "WARNING";
    }

    return "ONLINE";
}

function updateRobot(robot) {
    robot.battery -= Math.random() * 0.25;

    robot.temperature += (Math.random() - 0.5) * 1.2;

    robot.speed = Math.max(
        0,
        robot.speed + (Math.random() - 0.5) * 0.5
    );

    robot.battery = Math.max(0, robot.battery);

    robot.status = determineStatus(robot);
}

function renderRobots() {
    const container = document.getElementById("robot-grid");

    if (!container) return;

    container.innerHTML = "";

    robots.forEach(robot => {
        const card = document.createElement("div");
        card.className = "robot-card";

        const statusClass = robot.status.toLowerCase();

        card.innerHTML = `
            <div class="robot-header">
                <div class="robot-name">${robot.id}</div>
                <span class="badge ${statusClass}">
                    ${robot.status}
                </span>
            </div>

            <div class="telemetry">

                <div class="metric">
                    <div class="metric-label">BATTERY</div>
                    <div class="metric-value">
                        ${robot.battery.toFixed(1)}%
                    </div>
                </div>

                <div class="metric">
                    <div class="metric-label">TEMPERATURE</div>
                    <div class="metric-value">
                        ${robot.temperature.toFixed(1)} °C
                    </div>
                </div>

                <div class="metric">
                    <div class="metric-label">SPEED</div>
                    <div class="metric-value">
                        ${robot.speed.toFixed(2)} m/s
                    </div>
                </div>

                <div class="metric">
                    <div class="metric-label">STATE</div>
                    <div class="metric-value">
                        ${robot.status}
                    </div>
                </div>

            </div>
        `;

        container.appendChild(card);
    });

    updateSummary();
}

function updateSummary() {
    const online = robots.filter(r => r.status === "ONLINE").length;
    const warning = robots.filter(r => r.status === "WARNING").length;
    const critical = robots.filter(r => r.status === "CRITICAL").length;

    const avgBattery =
        robots.reduce((sum, robot) => sum + robot.battery, 0) /
        robots.length;

    const totalElement = document.getElementById("total-robots");
    const onlineElement = document.getElementById("online-robots");
    const alertElement = document.getElementById("alerts");
    const batteryElement = document.getElementById("avg-battery");
    const updateElement = document.getElementById("last-update");

    if (totalElement) {
        totalElement.textContent = robots.length;
    }

    if (onlineElement) {
        onlineElement.textContent = online;
    }

    if (alertElement) {
        alertElement.textContent = warning + critical;
    }

    if (batteryElement) {
        batteryElement.textContent = `${avgBattery.toFixed(1)}%`;
    }

    if (updateElement) {
        updateElement.textContent =
            `Last update: ${new Date().toLocaleTimeString()}`;
    }
}

function addEvent(message) {
    const eventLog = document.getElementById("event-log");

    if (!eventLog) return;

    const event = document.createElement("div");
    event.className = "event";

    event.innerHTML = `
        <span class="event-time">
            ${new Date().toLocaleTimeString()}
        </span>

        <span class="event-message">
            ${message}
        </span>
    `;

    eventLog.prepend(event);

    while (eventLog.children.length > 6) {
        eventLog.removeChild(eventLog.lastChild);
    }
}

function simulationCycle() {
    robots.forEach(robot => {
        const previousStatus = robot.status;

        updateRobot(robot);

        if (previousStatus !== robot.status) {
            addEvent(
                `${robot.id} changed from ${previousStatus} to ${robot.status}`
            );
        }
    });

    renderRobots();
}

renderRobots();

addEvent("RobotOps monitoring system initialized");
addEvent("Telemetry stream connected");
addEvent("5 robots registered with fleet controller");

setInterval(simulationCycle, 2000);
