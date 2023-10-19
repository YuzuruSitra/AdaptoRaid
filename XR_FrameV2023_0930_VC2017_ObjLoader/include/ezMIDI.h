//#pragma once
#ifndef EZMIDI_H
#define EZMIDI_H
#include <windows.h>
//#include <mmeapi.h> //// 20220925�ǉ�
#include <mmsystem.h> //// 20221114�ǉ�
#include <stdio.h>

/*
No.HEX

//�h�����Z�b�g���蓖��
35�@Acoustic Bass Drum	
38�@Acoustic Snare
41�@Low Floor Tom
45�@Low Tom
47�@Low Mid Tom
44�@Pedal Hi-Hat
49�@Crash Cymbal 1
51�@Ride Cymbal 1

// #01 PIANO

1 00 Acoustic Piano �A�R�[�X�e�B�b�N�s�A�m 
2 01 Bright Piano �u���C�g�s�A�m 
3 02 Electric Grand Piano �G���N�g���b�N�O�����h�s�A�m 
4 03 Honky-tonk Piano �z���L�[�g���N�s�A�m 
5 04 Electric Piano �G���N�g���b�N�s�A�m 
6 05 Electric Piano 2 �G���N�g���b�N�s�A�m2 
7 06 Harpsichord �n�[�v�V�R�[�h 
8 07 Clavi �N���r�l�b�g 

// #02 Chromatic Percussion

9 08 Celesta �`�F���X�^ 
10 09 Glockenspiel �O���b�P���V���s�[�� 
11 0A Musical box �I���S�[�� 
12 0B Vibraphone ���B�u���t�H�� 
13 0C Marimba �}�����o 
14 0D Xylophone �V���t�H�� 
15 0E Tubular Bell �`���[�u���[�x�� 
16 0F Dulcimer �_���V�}�[ 

// #03 Organ

17 10 Drawbar Organ �h���[�o�[�I���K�� 
18 11 Percussive Organ �p�[�J�b�V�u�I���K�� 
19 12 Rock Organ ���b�N�I���K�� 
20 13 Church organ �`���[�`�I���K�� 
21 14 Reed organ ���[�h�I���K�� 
22 15 Accordion �A�R�[�f�B�I�� 
23 16 Harmonica �n�[���j�J 
24 17 Tango Accordion �^���S�A�R�[�f�B�I�� 

// #04 Guitar

25 18 Acoustic Guitar (nylon) �A�R�[�X�e�B�b�N�M�^�[�i�i�C�������j 
26 19 Acoustic Guitar (steel) �A�R�[�X�e�B�b�N�M�^�[�i�X�`�[�����j 
27 1A Electric Guitar (jazz) �W���Y�M�^�[ 
28 1B Electric Guitar (clean) �N���[���M�^�[ 
29 1C Electric Guitar (muted) �~���[�g�M�^�[ 
30 1D Overdriven Guitar �I�[�o�[�h���C�u�M�^�[ 
31 1E Distortion Guitar �f�B�X�g�[�V�����M�^�[ 
32 1F Guitar harmonics �M�^�[�n�[���j�N�X 

// #05 Bass

33 20 Acoustic Bass �A�R�[�X�e�B�b�N�x�[�X 
34 21 Electric Bass (finger) �t�B���K�[�E�x�[�X 
35 22 Electric Bass (pick) �s�b�N�E�x�[�X 
36 23 Fretless Bass �t���b�g���X�x�[�X 
37 24 Slap Bass 1 �X���b�v�x�[�X 1 
38 25 Slap Bass 2 �X���b�v�x�[�X 2 
39 26 Synth Bass 1 �V���Z�x�[�X 1 
40 27 Synth Bass 2 �V���Z�x�[�X 2 

// #06 Strings

41 28 Violin ���@�C�I���� 
42 29 Viola ���B�I�� 
43 2A Cello �`�F�� 
44 2B Double bass �R���g���o�X 
45 2C Tremolo Strings �g������ 
46 2D Pizzicato Strings �s�b�`�J�[�g 
47 2E Orchestral Harp �n�[�v 
48 2F Timpani �e�B���p�j 

// #07 Ensemble

49 30 String Ensemble 1 �X�g�����O�A���T���u�� 1 
50 31 String Ensemble 2 �X�g�����O�A���T���u�� 2 
51 32 Synth Strings 1 �V���Z�X�g�����O�X 1 
52 33 Synth Strings 2 �V���Z�X�g�����O�X 2 
53 34 Voice Aahs ���u���[�v 
54 35 Voice Oohs ���u���[�v 
55 36 Synth Voice �V���Z���H�C�X 
56 37 Orchestra Hit �I�[�P�X�g���q�b�g 

// #08 Brass

57 38 Trumpet �g�����y�b�g 
58 39 Trombone �g�����{�[�� 
59 3A Tuba �`���[�o 
60 3B Muted Trumpet �~���[�g�g�����y�b�g 
61 3C French horn �t�����`�E�z���� 
62 3D Brass Section �u���X�Z�N�V���� 
63 3E Synth Brass 1 �V���Z�u���X 1 
64 3F Synth Brass 2 �V���Z�u���X 2 

// #09 Reed

65 40 Soprano Sax �\�v���m�T�b�N�X 
66 41 Alto Sax �A���g�T�b�N�X 
67 42 Tenor Sax �e�i�[�T�b�N�X 
68 43 Baritone Sax �o���g���T�b�N�X 
69 44 Oboe �I�[�{�G 
70 45 English Horn �C���O���b�V���z���� 
71 46 Bassoon �t�@�S�b�g 
72 47 Clarinet �N�����l�b�g 

// #10 Pipe

73 48 Piccolo �s�b�R�� 
74 49 Flute �t���[�g 
75 4A Recorder ���R�[�_�[ 
76 4B Pan Flute �p���t���[�g 
77 4C Blown Bottle ���r 
78 4D Shakuhachi �ڔ� 
79 4E Whistle ���J 
80 4F Ocarina �I�J���i 

// #11 Synth Lead

81 50 Lead 1 (square) ��`�g 
82 51 Lead 2 (sawtooth) �m�R�M���g 
83 52 Lead 3 (calliope) �J���I�y 
84 53 Lead 4 (chiff) �`�t 
85 54 Lead 5 (charang) �`�������S 
86 55 Lead 6 (voice) �� 
87 56 Lead 7 (fifths) �t�B�t�X�Y 
88 57 Lead 8 (bass + lead) �o�X + ���[�h 

// #12 Synth Pad

89 58 Pad 1 (Fantasia) �t�@���^�W�A 
90 59 Pad 2 (warm) �E�H�[�� 
91 5A Pad 3 (polysynth) �|���V���Z 
92 5B Pad 4 (choir) �N���C�A 
93 5C Pad 5 (bowed) �{�E 
94 5D Pad 6 (metallic) ���^���b�N 
95 5E Pad 7 (halo) �n���[ 
96 5F Pad 8 (sweep) �X�E�B�[�v 

// #13 Synth Effects

97 60 FX 1 (rain) �J 
98 61 FX 2 (soundtrack) �T�E���h�g���b�N 
99 62 FX 3 (crystal) �N���X�^�� 
100 63 FX 4 (atmosphere) �A�g���X�t�B�A 
101 64 FX 5 (brightness) �u���C�g�l�X 
102 65 FX 6 (goblins) �S�u���� 
103 66 FX 7 (echoes) �G�R�[ 
104 67 FX 8 (sci-fi) �T�C�t�@�C 

// #14 Ethnic

105 68 Sitar �V�^�[�� 
106 69 Banjo �o���W���[ 
107 6A Shamisen �O���� 
108 6B Koto �� 
109 6C Kalimba �J�����o 
110 6D Bagpipe �o�O�p�C�v 
111 6E Fiddle �t�B�h�� 
112 6F Shanai �V���n�i�[�C 

// #15 Percussive

113 70 Tinkle Bell �e�B���N���x�� 
114 71 Agogo �A�S�S 
115 72 Steel Drums �X�`�[���h���� 
116 73 Woodblock �E�b�h�u���b�N 
117 74 Taiko Drum ���� 
118 75 Melodic Tom �����f�B�b�N�^�� 
119 76 Synth Drum �V���Z�h���� 
120 77 Reverse Cymbal �t�V���o�� 

// #16 Sound effects

121 78 Guitar Fret Noise �M�^�[�t���b�g�m�C�Y 
122 79 Breath Noise �u���X�m�C�Y 
123 7A Seashore �C�� 
124 7B Bird Tweet ���̚��� 
125 7C Telephone Ring �d�b�̃x�� 
126 7D Helicopter �w���R�v�^�[ 
127 7E Applause ���� 
128 7F Gunshot �e�� 
*/
/*-----------------------------------------------------------------*/
class ezMIDI{
  public:
  /*----------------*/
  ezMIDI( int ch = 0, int tone = 0x60 ){
    _channel = ch;
	_tone = tone;
    _volume = 0x60;
	Send( 0xc0, _tone, 0x00 );
  }
  ~ezMIDI(){};

  /*----------------*/
  /* midi�f�o�C�X�I�[�v��*/
  static int Open( bool poly = false ){
    int ret;
    ret = midiOutOpen( &_hMidi, MIDIMAPPER, 0, 0, 0 );
    if( ret != 0 ) printf("error to open midi\n");
	polyphonic = poly;

    return ret;
  }
  /*----------------*/
  /* midi�f�o�C�X�N���[�Y*/
  static int Close(){
    int ret;
    ret = midiOutClose( _hMidi);
    if( ret != 0 ) printf("error to close midi\n");
    return ret;
  }
  /*----------------*/
  /* midi�f�o�C�X�̏C�� */
  static int Reset(){
	  int ret;
	  ret = midiOutReset( _hMidi );
      if( ret != 0 ) printf("error to close midi\n");
	  return ret;
  }
  /*----------------*/
  /* ����炷�@midi�f�o�C�X��midi�R�[�h��]�� */
  int Send( int stat, int data1, int data2 ){
    midiOutShortMsg( _hMidi, _PackMIDI( stat, data1 ,data2 ));
    return 0;
  }
  /*----------------*/
  /*----------------*/
  void Play( int pitch, int volume = 0x60 )
  {
      if( !polyphonic ){
	      Send( 0x90, _pitch, 0x00 );
	  }
	  else{

	  }
      Send( 0x90, pitch, 0x00 );
	  if( volume == 0 ) Send( 0x90, pitch, 0 );
	  else Send( 0x90, pitch, _volume );
	  _pitch = pitch;
  }
  int Mute( void )
  {
  }

  /*----------------*/
  void SetVolume( int vol ){
    _volume = vol;
  }
  static HMIDIOUT _hMidi;/* midi�f�o�C�X�n���h��*/
  static bool polyphonic;



  private:
  int _channel;
  int _tone;
  int _pitch;
  int _volume;
  int _panpot;

  /*----------------*/
  DWORD _PackMIDI( int stat, int data1, int data2 ){
    return (DWORD)( stat|_channel |(data1 << 8)|(data2 << 16));
  }
};
#endif
