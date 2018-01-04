# TowersOfHanoi
Towers of Hanoi - recursion exercise

//******************************************
// a is a field showing position of discs
//   (of a size) on poles
//
// EXAMPLE 1:
//                          #|       |       |
//     {[4,3,2,1...]       ##|       |       |
// a =  [0,0,0,0...]  =   ###|       |       |
//      [0,0,0,0...]}    ####|       |       |
//                       pole0   pole1    pole2
//
//
// EXAMPLE 2:
//                            |       |       |
//      {[4,3,0,0...]         |       |       |
// a =   [0,0,0,0...]   =  ###|       |      #|
//       [2,1,0,0...]}    ####|       |     ##|
//                       pole0   pole1    pole2
//
//
//
// src = source
// dst = destination
// spr = spare
//******************************************
//******************************************
// PSEUDO CODE (WIKI)
//A = [5, 4, 3, 2, 1]
//B = []
//C = []
//
//def move(n, source, target, auxiliary):
//    if n > 0:
//        # move n - 1 disks from source to auxiliary, so they are out of the way
//        move(n - 1, source, auxiliary, target)
//
//        # move the nth disk from source to target
//        target.append(source.pop())
//
//        # Display our progress
//        print(A, B, C, '##############', sep = '\n')
//
//        # move the n - 1 disks that we left on auxiliary onto target
//        move(n - 1, auxiliary, target, source)

//******************************************
