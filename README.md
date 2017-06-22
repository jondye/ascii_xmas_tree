## Assumptions

- C++14 has been assumed as the target language.

## Design notes

- Trees have a width and a height which determines the average slope of the tree.
- Branches have a shallower slope than the average slope of the tree.
- The angle of the branch slope and the number of layers of tree determine the shape of the tree.
- Placement of stars and baubles is random. For simplicity no effort has been made to avoid clumping of decorations together.

## Implementation notes

The specification does not state the importance of performance therefore the
implementation is intended to be simpler to read rather than focusing on
performance.

Floating point numers are used to calculate slopes and height of branhes. This
is for simplicitly of implementation. Floating point numbers could be
eliminated and integer maths could be used instead if desirable.  Techniques
similar to Breshenham's line algorithm can be used.

The text to display is created in a buffer (std::string) before being written
out. It is assumed that the compiler will optimise away all copies/moves of
std::string, e.g. using Named Return Value (NRV) optimisation. Heap allocations
will, however remain. Again, this approach was chosen for simplicity.
