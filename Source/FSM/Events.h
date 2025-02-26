#pragma once
#include <variant>
#include <FSM/FSMEvent.h>
struct EventStartedShooting : FSMEvent { EventStartedShooting() : FSMEvent() { setName("StartedShooting"); } };
struct EventStartedMoving : FSMEvent { EventStartedMoving() : FSMEvent() { setName("StartedMoving"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventStoppedShooting : FSMEvent { EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };