import java.util.Date;

public class Application_eightQueen {
	private static final short N=8;        //ʹ�ó��������壬����֮���N�ʺ�����
    private static int count=0;            //���������
    
    public static void main(String[] args) {
        Date begin =new Date();
        //��ʼ�����̣�ȫ����0
        short chess[][]=new short[N][N];
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                chess[i][j]=0;
            }
        }
        
        putQueenAtRow(chess,0);
        Date end =new Date();
        System.out.println("��� " +N+ " �ʺ����⣬��ʱ��" +String.valueOf(end.getTime()-begin.getTime())+ "���룬��������"+count);
    }

    private static void putQueenAtRow(short[][] chess, int row) {        
        /**
         * �ݹ���ֹ�жϣ����row==N����˵���Ѿ��ɹ��ڷ���8���ʺ�
         * ����������ֹ�ݹ�
         */
        if(row==N){
            count++;
     /*       System.out.println("�� "+ count +" �ֽ⣺");
           for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    System.out.print(chess[i][j]+" ");
                }
               System.out.println();
           }*/
            return;
        }
        
        short[][] chessTemp=chess.clone();
        
        /**
         * ����һ�е�ÿһ��λ�ó����ŷŻʺ�
         * Ȼ����״̬�������ȫ�����ִ�еݹ麯���ڷ���һ�лʺ�
         */
        for(int i=0;i<N;i++){
            //�ڷ���һ�еĻʺ�֮ǰҪ���������һ�аڷŵļ�¼����ֹ��Ⱦ����
            for(int j=0;j<N;j++)
                chessTemp[row][j]=0;
            chessTemp[row][i]=1;
            
            if( isSafety( chessTemp,row,i ) ){
                putQueenAtRow(chessTemp,row+1);
            }
        }
    }

    private static boolean isSafety(short[][] chess,int row,int col) {
        //�ж����ϡ����ϡ������Ƿ�ȫ
        int step=1;
        while(row-step>=0){
            if(chess[row-step][col]==1)                //����
                return false;
            if(col-step>=0 && chess[row-step][col-step]==1)        //����
                return false;
            if(col+step<N && chess[row-step][col+step]==1)        //����
                return false;
            
            step++;
        }
        return true;
    }
}