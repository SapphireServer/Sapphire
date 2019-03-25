# Contributing

Thanks for contributing to Sapphire!

First, we'd like to mention that a lot of discussion regarding the project happens in our Discord server.
We value research and discussion as to how we should tackle our issues as well as improving what is already in.
Of course we also value testing - many things tend to break due to patches, or mistakes/edge cases.

Regardless of how you plan on contributing, your thoughts are appreciated and you're welcome to join our Discord (link in README.md).

## Research

Care in implementating features should be taken. It tends to be end up weird, and replicating the expected behavior 
is always preferred. Avoid assumptions and guesswork whenever possible.

As much research possible should be done before writing it out - on game data, testing with retail, 
and even common practices in server development (emulators or not).

## Pull Requests

When making a PR, please make sure that it follows our style guidelines and good practices.

### Coding style

Indentations are Allman-style based, 2-space, no tabs.
Space between arguments in function calls, as well as for types.

Example (shortened from ActionHandler.cpp):

```cpp
switch( commandId )
{
  case 0x01:  // Toggle sheathe
  {
    if( param11 == 1 )
       pPlayer->setStance( Entity::Chara::Stance::Active );
    else
    {
      pPlayer->setStance( Entity::Chara::Stance::Passive );
      pPlayer->setAutoattack( false );
    }

    pPlayer->sendToInRangeSet( ActorControlPacket142( pPlayer->getId(), 0, param11, 1 ) );

    break;
  }
  case 0x03: // Change target
  {
    uint64_t targetId = inPacket.getValAt< uint64_t >( 0x24 );
    pPlayer->changeTarget( targetId );
    break;
  }
  default:
  {
    break;
  }
}
```

### Feature implementation

Please make sure edge cases have been tested, behavior is aligned with retail and (if applicable) your queries make sense.
Any changes to the SQL base should be noted (and reflected in the update.sql file in rootDirectory/sql). 
