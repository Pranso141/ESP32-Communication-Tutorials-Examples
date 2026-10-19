#include "painlessMesh.h"

// Define network credentials (must be identical on all mesh nodes)
#define MESH_PREFIX    "ESP_MESH_DEMO"
#define MESH_PASSWORD  "MeshPassword123"
#define MESH_PORT      5555

Scheduler userScheduler;
painlessMesh mesh;

// Function declarations
void sendMessage();
Task taskSendMessage(TASK_SECOND * 3, TASK_FOREVER, &sendMessage);

void sendMessage() {
  String msg = "Hello from Node: ";
  msg += mesh.getNodeId();
  mesh.sendBroadcast(msg);
}

// Callback when a message is received from another node
void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
}

// Callback when a new node joins the network
void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> New Connection, nodeId = %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);

  // Configure mesh debug messages
  mesh.setDebugMsgTypes(ERROR | STARTUP);

  // Initialize the mesh network
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  // Schedule periodic task execution
  userScheduler.addTask(taskSendMessage);
  taskSendMessage.enable();
}

void loop() {
  // Keeps mesh background processes active
  mesh.update();
}
