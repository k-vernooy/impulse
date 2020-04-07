# impulse
A cellular-automata based music visualizer for terminal

## Installation

```
git clone 'https://github.com/k-vernooy/impulse'
cd impulse
make
```

or through homebrew (coming soon):

```
brew tap k-vernooy/tap
brew install impulse
```

## Usage
```
impulse <in.wav> [options]
```
Must input a wav or [format] audio file in order to visualize it.


## Dependencies
Impulse depends on a terminal audio player. This can be configured through
```
impulse --configure mp=[your_media_player] options=[flags_to_pass]
```
