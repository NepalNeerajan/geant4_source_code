//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4RTOutBitStream.cc,v 1.4 2001/07/11 10:09:04 gunter Exp $
// GEANT4 tag $Name: geant4-04-01 $
//
//
//

#include <string.h>
#include "G4RTJpeg.hh"
#include "G4RTOutBitStream.hh"



G4OutBitStream::G4OutBitStream(int size)
{
  if(size < 1)
        throw( G4MemoryError( size, "G4OutBitStream" ) );

  mHeadOfBuf = mBuf = new u_char[size];
  if( mHeadOfBuf == 0 )
        throw( G4MemoryError( size, "G4OutBitStream" ) );

  mEndOfBuf = mBuf + size;

  memset( mHeadOfBuf, 0, size );

  mBitPos = 7;
  mWriteFlag = 1;
}

void
G4OutBitStream::IncBuf( void )
{
  if( ++mBuf >= mEndOfBuf )
        mWriteFlag = 0;
}



void
G4OutBitStream::SetBits(int v, int numBits)
{
  if( numBits == 0 )
        return;
  if( numBits > 16 )
        throw( G4BufferError( "SetBits:Max Bit Over" ) );
  if( numBits > 8 ){
        Set8Bits( u_char(v>>8), numBits-8 );
        numBits = 8;
  }
  Set8Bits( u_char(v), numBits );
}

void
G4OutBitStream::SetFewBits(u_char v, int numBits)
{
  v &= BitFullMaskT[numBits-1];
  *mBuf |= v << (mBitPos + 1 - numBits);
  if( (mBitPos -= numBits) < 0 ){
        if( *mBuf == 0xff ){
          IncBuf();
          *mBuf = 0;
        }
        IncBuf();
        mBitPos = 7;
    }
}

void
G4OutBitStream::SetBits2Byte(u_char v, int numBits)
{
  v &= BitFullMaskT[numBits-1];
  int nextBits = numBits - (mBitPos + 1);
  *mBuf |= ( v >> nextBits ) & BitFullMaskT[mBitPos];
  if( *mBuf == 0xff ){
        IncBuf();
        *mBuf = 0;
  }
  IncBuf();

  *mBuf = v << 8 - nextBits;
  mBitPos = 7 - nextBits;
}

void
G4OutBitStream::Set8Bits(u_char v, int numBits)
{
  if( mBitPos + 1 >= numBits )
        SetFewBits( (u_char)v, numBits );
 else
        SetBits2Byte( (u_char)v, numBits );
}


void
G4OutBitStream::FullBit( void )
{
  if( mBitPos != 7 )
        SetFewBits( BitFullMaskT[mBitPos], mBitPos+1 );
}

void
G4OutBitStream::SetByte(u_char dat)
{
  if( mWriteFlag ){
        FullBit();
        *mBuf = dat;
        IncBuf();
        return;
  }
  throw( G4BufferError( "SetByte" ) );
}

void
G4OutBitStream::SetWord(u_int dat)
{
  if( mWriteFlag ){
        FullBit();
        *mBuf = (dat >> 8) & 0xff;
        IncBuf();
        *mBuf = dat & 0xff;
        IncBuf();
        return;
  }
  throw( G4BufferError( "SetWord" ) );
}

void
G4OutBitStream::CopyByte(const char* src, int n)
{
  if( mBuf+n < mEndOfBuf ){
        FullBit();
        memcpy( mBuf, src, n );
        mBuf += n;
        return;
  }
  throw( G4BufferError( "CopyByte" ) );
}
