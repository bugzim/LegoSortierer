import com.fazecast.jSerialComm.SerialPort;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;
import java.sql.SQLException;

public class Packy {
	
	public static void main (String[] args) {
		
		System.out.println("Connected to DB");
		convertByteToString();
		
	}
	
	public static void connect() {
        // connection string
        var url = "jdbc:sqlite:/home/robinnordhausen/ArduinoSerialReader/legoStorage.db";

        try (Connection conn = DriverManager.getConnection(url)) {
			
			String sql = "SELECT * FROM farben";
					
			Statement stmt = conn.createStatement();
			stmt.execute(sql);
			
            System.out.println("Connection to SQLite has been established.");
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }        
    }
		
	public static void convertByteToString() { 
		SerialPort[] ports = SerialPort.getCommPorts();
		
		SerialPort port = ports[0]; //open the port
                                   //Arduino May get reset
               //Partial Code only
			int BaudRate = 9600;
			int DataBits = 8;
			int StopBits = SerialPort.ONE_STOP_BIT;
			int Parity   = SerialPort.NO_PARITY;
			//Sets all serial port parameters at one time
			port.setComPortParameters(BaudRate,
											  DataBits,
											  StopBits,
											   Parity);
			//Set Read Time outs
			port.setComPortTimeouts(SerialPort.TIMEOUT_READ_BLOCKING, 
                                1000, 
                                   0);                    
             port.openPort();
             	
			   try 
			{
			   while (true)
			   {
				 byte[] readBuffer = new byte[100];
				 int numRead = port.readBytes(readBuffer,
													  readBuffer.length);
				 
			//Convert bytes to String
			String arduinoString = new String(readBuffer, "UTF-8");
			char color = arduinoString.charAt(0);
				 
			var url = "jdbc:sqlite:/home/robinnordhausen/ArduinoSerialReader/legoStorage.db";
				 
			Connection conn = DriverManager.getConnection(url);
				 
			Statement stmt = conn.createStatement();
			
			 switch(color) {
					 case 'r': 
						String plusRed = "update farben set r = r + 1";
						stmt.execute(plusRed);
					 break;
					 case 'g':
						String plusGreen = "update farben set g = g + 1";
						stmt.execute(plusGreen);
					 break;
					 case 'b':
						String plusBlue = "update farben set b = b + 1";
						stmt.execute(plusBlue);
					 break;
					 case 'c':
						String plusCyan = "update farben set c = c + 1";
						stmt.execute(plusCyan);
					 break;
					 case 'y':
						String plusYellow = "update farben set y = y + 1";
						stmt.execute(plusYellow);
					 break;
					 case 'm':
						String plusMagenta = "update farben set m = m + 1";
						stmt.execute(plusMagenta);
					 break;
					 case 'w':
						String plusWhite = "update farben set w = w + 1";
						stmt.execute(plusWhite);
					 break;
				}
			
		}
		   }
			
			catch (Exception e) 
			{
				 e.printStackTrace(); 
			}
			port.closePort(); 
		}
    
}

