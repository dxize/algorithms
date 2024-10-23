{
9.  �   ���������   �����   �����������   �������  ��������
���������.  ����������  ����  ���,  �����  �������  ����������
���������� ������� (6).

����� ����������: Gnu pascal

��������� ������� ���� ����� ��������� � ��������� ANSI � ����

��������: �������� ����� ��-21
}


PROGRAM MainWords(INPUT, OUTPUT);
VAR
  F1, F2: TEXT;
  NameInputFile, NameOutputFile: STRING;
  Ch: CHAR;

PROCEDURE UpperCaseCh(VAR Ch: CHAR);
BEGIN
  CASE Ch OF
    'a' : Ch := 'A';
    'b' : Ch := 'B';
    'c' : Ch := 'C';
    'd' : Ch := 'D';
    'e' : Ch := 'E';
    'f' : Ch := 'F';
    'g' : Ch := 'G';
    'h' : Ch := 'H';
    'i' : Ch := 'I';
    'j' : Ch := 'J';
    'k' : Ch := 'K';
    'l' : Ch := 'L';
    'm' : Ch := 'M';
    'n' : Ch := 'N';
    'o' : Ch := 'O';
    'p' : Ch := 'P';
    'q' : Ch := 'Q';
    'r' : Ch := 'R';
    's' : Ch := 'S';
    't' : Ch := 'T';
    'u' : Ch := 'U';
    'v' : Ch := 'V';
    'w' : Ch := 'W';
    'x' : Ch := 'X';
    'y' : Ch := 'Y';
    'z' : Ch := 'Z';

    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�';
    '�' : Ch := '�'
  ELSE
    WRITE(OUTPUT, '���������������� ������: ', Ch)
  END
END;

BEGIN
  WRITE('������� ��� �������� �����: ');
  READLN(NameInputFile); 

  WRITE('������� ��� ��������� �����: ');
  READLN(NameOutputFile);

  ASSIGN(F1, NameInputFile);
  {$I-}  { ��������� �������������� ��������� ������ �����-������ }
  RESET(F1);
  {$I+}  { �������� �������������� ��������� ������ ������� }

  IF IOResult <> 0
  THEN
    BEGIN
      WRITELN('������ �������� �������� �����: ', NameInputFile);
      CLOSE(F1);
      EXIT  { ��������� ��������� � ������ ������ }
    END;

  ASSIGN(F2, NameOutputFile);
  {$I-}
  REWRITE(F2);
  {$I+}

  IF IOResult <> 0 
  THEN
    BEGIN
      WRITELN('������ �������� ��������� �����: ', NameOutputFile);
      CLOSE(F2);
      EXIT
    END;

  WHILE NOT EOF(F1) 
  DO
    BEGIN
      WHILE NOT EOLN(F1) 
      DO
        BEGIN      
          READ(F1, Ch);
          IF Ch <> '"' 
          THEN
            WRITE(F2, Ch)
          ELSE
            BEGIN
              READ(F1, Ch);
              WHILE (Ch <> '"') AND NOT EOLN(F1) 
              DO
                BEGIN
                  UpperCaseCh(Ch);
                  WRITE(F2, Ch);
                  READ(F1, Ch)
                END
            END
        END;
      READLN(F1);
      WRITELN(F2)
    END;

  CLOSE(F1);  { ��������� ������� ���� }
  CLOSE(F2);  { ��������� �������� ���� }
END.

