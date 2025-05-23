//
// Created by romain on 23/05/25.
//

#ifndef RTTI_H
#define RTTI_H

// On utilise les pointeurs dynamiques, et leurs propriétés de renvoyer nullptr dans le cas où ils
// leurs est demandé de convertir un objet en quelque chose qui n'est pas une de ses sous-classes.

// Ces variables sont donc pour vérifier si le compilateur va le supporter.

#if !defined(cxx_rtti) && !defined(_CPPRTTI) && !defined(__GXX_RTTI)
#error no rtti for dynamic pointers
#endif

#endif //RTTI_H
