#include <stdio.h>
#include <string.h>

//����ȫ�ֱ����ͺ���
char ch, prog[200], token[8];//chΪ�û������ÿ���ַ�,prog[]����û�����ĳ������,token[]��Ŵӳ�������л��ֳ��ĵ��������ַ���
int syn, p, m, n, num;//synΪ�����ֱ���,p��Ϊ�����±�ָ�����ڱ���prog[]�����prog[]���鸳ֵ
char* rwtab[6] = { "begin", "if", "then", "while", "do", "end"};//���6���ؼ��ֵ��ʵ��ַ���ָ������rwtab,ָ��6���ַ���
int scanner();//����������ҵ�ɨ�躯��



int main()//������
{
	p = 0;//��ʼ��ָ��
	printf("��������ȷ��ʽ�����:\n");
	do {
		scanf("%c", &ch);
		prog[p++] = ch;//���û�������ַ���Ž����������,����������#
	} while (ch != '#');//����������#�˳�ѭ��
	p = 0;
	do {//��prog��ĳ�����ӽ��е����зֲ������ж�
		scanner();
		switch (syn)
		{
		case 11:printf("( %d , %d )\n", syn, num);
			break;
		case -1:printf("��һ���Ƿ��ĵ���\n");
			break;
		default: printf("( %d , %s )\n", syn, token);
			break;
		}
	} while (syn != 0);
}


//ɨ�������ӻ��ֳ�����
int scanner()
{
	memset(token,0,8);
	m = 0;//ƴ�ӵ����ַ��� 	
	num = 0;//��Ϊ���������ַ��������Ƚ������ַ���ת��Ϊ��ֵ��������ֵ0

	ch = prog[p++];//������ӵĵ�һ���ַ�����ch
	while((ch == ' ')||(ch == '\n')) ch = prog[p++];//��ɨ�赽���ַ��ǿո�����ǻ��з�,���������

	if(((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A')))//������������ַ�����ĸ
	{
		while (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A')) || ((ch >= '0') && (ch <= '9')))//�������������ַ�������ĸ������
		{
			token[m++] = ch;//������������������ĸ�����ָ���token[]����
			ch = prog[p++];
		}
         syn = 10;//����token�������ŵĵ��ʷ��Ų�Ϊ�ؼ���,����Ӧ�ֱ���10
		p--;//ָ�����һλ
	
	    //��������֤�Ƿ�Ϊ�ؼ��ֵ����
		for (n = 0; n <=5; n++) {//���ַ�������ƥ��
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;//ƥ��ɹ����ֱ���Ϊn+1
				break;//һ��ƥ��ɹ�����forѭ��
			}
		}
		//û��ƥ����֤��Ϊletter(letter|digit)��synȡΪ10
	}
		


	else if((ch>='0')&&(ch<='9'))//����������ַ�Ϊ����
	{
		int p1=p;
	    while((ch>='0')&&(ch<='9'))
		{
			num = num * 10 + ch - '0';//���ַ�ת��Ϊ���ֲ����ۼӺ�
			ch = prog[p++];
		}

		if (((ch <= 'z') && (ch >= 'a')) || ((ch <= 'Z') && (ch >= 'A'))) {//�����������ֿ�ͷ�ĵ����ں�����ĸ
			syn = -1;//��syn=1��ʾ����,
			int p2 = p1-1;//p2ָ���һ���ַ�
			printf("%c",prog[p2]); 
			for(p1;p1<p;p1++)
			{
				printf("%c ",prog[p1]);//�������ַ��������ֲ��ִ�ӡ��
			}
			
		}

		else {//Ϊ�����������ַ�

			p--;//���һ��ָ�����һλ
			syn = 11;//ƥ��ɹ�,Ϊdigit digit*��,syn=11
		}

	}


/*����������������Ž���ƥ��:
  ���ڵ����ַ��������,ֱ��ƥ��;
  ���ڶ���ַ��������,���������ַ���ƥ��Ĺ���*/

	else switch (ch){

	case '<': token[m++] = ch;//'<'�ַ���Ҫ����һ����ȡһ���ַ������ж�
	 	      ch = prog[p++];//�Ƚ�'<'д��token����Ȼ��pָ����� 

	 	      if (ch == '=') //'<='���ʷ���
			  {
			  syn = 22;
			  token[m++] = ch; //'='д��token����
			  }
			  else if (ch == '>') { //'<>'���ʷ���
			  syn = 21;
			  token[m++] = ch; //'>'д��token����
			  }
		      else//ֻ��'<'�ַ�
			  {
			  syn = 20;
			  p--;//��ǰ�жϵ�ָ����Ҫ����һλ
			  }
			  break;

	case '>': token[m++] = ch;
		      ch = prog[p++];
		      if (ch == '=')//'>='���ʷ���
			  {
			  syn = 24;
			  token[m++] = ch;//'='д��token����
			  }
		      else//ֻ��'>'�ַ�
			  {
		 	  syn = 23;
			  p--;//��ǰ�жϵ�ָ����Ҫ����һλ
			  }
		      break;
	case '+': token[m++] = ch;
		      syn = 13;
		      break;
	case '-': token[m++] = ch;
		      syn = 14;
		      break;
	case ':': token[m++] = ch;//'='��Ҫ����һ����ȡһ���ַ������ж�
		      ch = prog[p++];
		      if (ch == '=')//'=='���ʷ���
			  {
			  syn = 18;
			  token[m++] = ch;
			  }
		      else
			  {
			  syn = 17;
			  p--;
			  }
		      break;

	case '=': token[m++] = ch;
		      syn = 25;
		      break;
	case '*': syn = 15;
		      token[m++] = ch;
		      break;
	case '/': syn = 16;
		      token[m++] = ch;
		      break;
	case '(': syn = 27;
		      token[m++] = ch;
		      break;
	case ')': syn = 28;
		      token[m++] = ch;
		      break;
	case '{': syn = 5;
		      token[m++] = ch;
		      break;
	case '}': syn = 6;
		      token[m++] = ch;
		      break;
	case ';': syn = 26;
		      token[m++] = ch;
		      break;
	case '\"': syn = 30;
		       token[m++] = ch;
		       break;
	case '#': syn = 0;
		      token[m++] = ch;
		      break;
	default: syn = -1;//û��ƥ�䵽�κ�һ��,���ش���
		printf(" %c ",ch);
		      break;
	}
	token[m++] = '\0';//���ַ���������־
	return 0;
}
