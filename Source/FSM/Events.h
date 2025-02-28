#pragma once
#include <variant>
#include <FSM/FSMEvent.h>
struct EventStartedShooting : FSMEvent { EventStartedShooting() : FSMEvent() { setName("StartedShooting"); } };
struct EventStartedMoving : FSMEvent { EventStartedMoving() : FSMEvent() { setName("StartedMoving"); } };
struct EventStoppedMoving : FSMEvent { EventStoppedMoving() : FSMEvent() { setName("StoppedMoving"); } };
struct EventStoppedShooting : FSMEvent { EventStoppedShooting() : FSMEvent() { setName("StoppedShooting"); } };
struct EventBeganJump : FSMEvent { EventBeganJump() : FSMEvent() { setName("BeganJump"); } };
struct EventLanding : FSMEvent { bool moving{ false };  EventLanding(bool moving_) : FSMEvent(), moving{ moving_ } { setName("Landing"); } };
