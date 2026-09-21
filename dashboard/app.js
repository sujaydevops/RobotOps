const TELEMETRY_FILE = "telemetry.csv";
const REFRESH_INTERVAL = 2000;

let previousStatuses = {};
let initialized = false;

async function loadTelemetry() {
    try {
        const response = await fetch(
            `${TELEMETRY_FILE}?t=${Date.now()}`,
            { cache: "no-store" }
        );

        if (!response.ok) {
            throw new Error(`HTTP ${response.status}`);
        }

        const csv = await response.text();
        const robots = parseTelemetry(csv);

        if (robots.length === 0) {
            throw new Error("No telemetry records found");
        }

        renderRobots(robots);
        updateSummary(robots);
        detectStatusChanges(robots);

        const updateElement = document.getElementById("last-update");

        if (updateElement) {
            updateElement.textContent =
                `Last telemetry update: ${new Date().toLocaleTimeString()}`;
        }

        if (!initialized) {
            addEvent("C++ telemetry stream connected");
            addEvent(`${robots.length} robots detected`);
            initialized = true;
        }

    } catch (error) {
        console.error("Telemetry error:", error);

        const updateElement = document.getElementById("last-update");

        if (updateElement) {
            updateElement.textContent = "Telemetry connection error";
        }
    }
}

function parseTelemetry(csv) {
    const lines = csv.trim().split(/\r?\n/);

    if (lines.length < 2) {
        return [];
    }

    const latest = new Map();

    for (let i = 1; i < lines.length; i++) {
        const columns = lines[i].split(",");

        if (columns.length < 9) {
            continue;
        }

        const robot = {
            timestamp: columns[0].trim(),
            id: columns[1].trim(),
            battery: Number(columns[2]),
            temperature: Number(columns[3]),
            speed: Number(columns[4]),
            xPosition: Number(columns[5]),
            yPosition: Number(columns[6]),
            status: columns[7].trim(),
            errorCode: columns[8].trim()
        };

        if (
            !robot.id ||
            !Number.isFinite(robot.battery) ||
            !Number.isFinite(robot.temperature) ||
            !Number.isFinite(robot.speed)
        ) {
            continue;
        }

        // Since the CSV is chronological, later rows replace
        // earlier rows for the same robot.
        latest.set(robot.id, robot);
    }

    return Array.from(latest.values())
        .sort((a, b) => a.id.localeCompare(b.id));
}

function renderRobots(robots) {
    const container = document.getElementById("robot-grid");

    if (!container) {
        return;
    }

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
                    <div class="metric-label">POSITION</div>
                    <div class="metric-value">
                        (${robot.xPosition.toFixed(2)},
                        ${robot.yPosition.toFixed(2)})
                    </div>
                </div>

                <div class="metric">
                    <div class="metric-label">ERROR CODE</div>
                    <div class="metric-value">
                        ${robot.errorCode}
                    </div>
                </div>

                <div class="metric">
                    <div class="metric-label">TELEMETRY TIME</div>
                    <div class="metric-value">
                        ${robot.timestamp}
                    </div>
                </div>

            </div>
        `;

        container.appendChild(card);
    });
}

function updateSummary(robots) {
    const online =
        robots.filter(robot => robot.status === "ONLINE").length;

    const alerts =
        robots.filter(robot =>
            robot.status === "WARNING" ||
            robot.status === "CRITICAL"
        ).length;

    const averageBattery =
        robots.reduce(
            (total, robot) => total + robot.battery,
            0
        ) / robots.length;

    setText("total-robots", robots.length);
    setText("online-robots", online);
    setText("alerts", alerts);
    setText("avg-battery", `${averageBattery.toFixed(1)}%`);
}

function detectStatusChanges(robots) {
    robots.forEach(robot => {
        const previous = previousStatuses[robot.id];

        if (previous && previous !== robot.status) {
            addEvent(
                `${robot.id} changed from ${previous} to ${robot.status}`
            );
        }

        previousStatuses[robot.id] = robot.status;
    });
}

function setText(id, value) {
    const element = document.getElementById(id);

    if (element) {
        element.textContent = value;
    }
}

function addEvent(message) {
    const eventLog = document.getElementById("event-log");

    if (!eventLog) {
        return;
    }

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

loadTelemetry();

setInterval(loadTelemetry, REFRESH_INTERVAL);
