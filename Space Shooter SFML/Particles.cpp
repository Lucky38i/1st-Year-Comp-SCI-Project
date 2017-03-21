#include "Particles.h"
#include "random.h"



Particles::Particles()
{
	thor::FadeAnimation fader(fadeIn, fadeOut); //Sets the time between the emitter fading in and out
	emitter.setEmissionRate(rate); //Set the rate at which particles are emitted per second
	emitter.setParticleLifetime(sf::seconds(lifeTime)); //sets the lifetime of the particles
	system.addEmitter(thor::refEmitter(emitter));
	system.addAffector(thor::TorqueAffector(50.f));
	system.addAffector(thor::ForceAffector(sf::Vector2f(0.f, 90.f)));
	//system.addAffector(thor::AnimationAffector(fader));
	
}

void Particles::update()
{

}


