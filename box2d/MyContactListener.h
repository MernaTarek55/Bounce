#pragma once
#include <vector>
#include "Ball.h"
#include "Collectible.h"
#include "Flag.h"
#include "Water.h"
#include "MaximizeBall.h"
#include "MinimizeBall.h"
#include "Spike.h"
class MyContactListener : public b2ContactListener {
public:
    MyContactListener(Ball& ball, std::vector<Collectible*>& collectibles, std::vector<Collectible*>& toRemove, bool& jumpFlag, Water& water, Flag& flag, std::vector<MaximizeBall*>& maximizeBalls,
        std::vector<MinimizeBall*>& minimizeBalls,
        std::vector<MaximizeBall*>& toRemoveMax,
        std::vector<MinimizeBall*>& toRemoveMin,
        Spike& spike)
        : ball(ball), maximizeBalls(maximizeBalls),
        minimizeBalls(minimizeBalls),
        toRemoveMax(toRemoveMax),
        toRemoveMin(toRemoveMin), collectibles(collectibles), toRemove(toRemove), isJumping(jumpFlag), water(water), flag(flag), spike(spike) {
    }

    void BeginContact(b2Contact* contact) override {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        // Check for ground contact
        if (bodyA == ball.getBody() || bodyB == ball.getBody()) {
            if (bodyA->GetType() == b2_staticBody || bodyB->GetType() == b2_staticBody) {
                isJumping = false;
            }
        }

        // Ball collides with water
        if ((bodyA == ball.getBody() && bodyB == water.getBody()) ||
            (bodyB == ball.getBody() && bodyA == water.getBody())) {
            printf("Ball collided with water!\n");
            if (ball.isMaximized) {
                ball.startWaveEffect(); // Trigger wave effect
                ballGravity = ball.getBody()->GetGravityScale();
                ball.getBody()->SetGravityScale(0.0);

            }
            water.startWaveEffect(); // Trigger wave effect
        }
        
        if ((bodyA == ball.getBody() && bodyB == spike.getBody()) || (bodyB == ball.getBody() && bodyA == spike.getBody())) {
            printf("sddddddddddddddddd"); // Test the log
            ball.decreaseLives();         // Trigger action
            ball.respawn();
        }
        

        // Ball collides with flag
        if ((bodyA == ball.getBody() && bodyB == flag.getBody()) ||
            (bodyB == ball.getBody() && bodyA == flag.getBody())) {
            printf("Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("Winner!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            flag.onCollision();
            ball.setCheckpoint(flag.getposition());
        }
        for (auto& minimizeBall : minimizeBalls) {
            if (bodyA == minimizeBall->getBody() || bodyB == minimizeBall->getBody()) {
                toRemoveMin.push_back(minimizeBall);
                //minimizeBall->onCollision(ball);
            }
        }

        // Check for collisions with maximize balls
        for (auto& maximizeBall : maximizeBalls) {
            if (bodyA == maximizeBall->getBody() || bodyB == maximizeBall->getBody()) {
                toRemoveMax.push_back(maximizeBall);
                //maximizeBall->onCollision(ball);
            }
        }
        // Check for collectible collision
        for (auto& collectible : collectibles) {
            if (bodyA == collectible->getBody() || bodyB == collectible->getBody()) {
                toRemove.push_back(collectible); // Mark collectible for removal
            }
        }
    }

    void EndContact(b2Contact* contact) override {
        b2Body* bodyA = contact->GetFixtureA()->GetBody();
        b2Body* bodyB = contact->GetFixtureB()->GetBody();

        // Ball exits water
        if ((bodyA == ball.getBody() && bodyB == water.getBody()) ||
            (bodyB == ball.getBody() && bodyA == water.getBody())) {
            printf("Ball exited the water!\n");
            ball.getBody()->SetGravityScale(ballGravity);
        }
    }

private:
    Ball& ball;
    
    std::vector<Collectible*>& collectibles;
    Spike& spike;
    std::vector<Collectible*>& toRemove;
    bool& isJumping;
    Water& water;
    Flag& flag;
    float ballGravity;
    std::vector<MaximizeBall*>& maximizeBalls;
    std::vector<MinimizeBall*>& minimizeBalls;
    std::vector<MaximizeBall*>& toRemoveMax;
    std::vector<MinimizeBall*>& toRemoveMin;
};  