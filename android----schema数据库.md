### 如果没有“主题框”

* 检查style里面的类和fragment继承的类是不是一致的。


### 数据库(schema)

①创建一个包，用来放数据库相关类（包名为database）

②新建一个类，用来存放tabel相关数据
```java
public class CrimeDbSchema {
    public static final class CrimeTable {
        public static final String NAME = "crimes";

        public static final class Cols {
            public static final String UUID = "uuid";
            public static final String TITLE = "title";
            public static final String DATE = "date";
            public static final String SOLVED = "solved";
            public static final String SUSPECT = "suspect";
        }
    }
}
```

③再新建一个类，继承于SQLiteOpenHelper---用来帮助我们对数据进行存取

```java
public class CrimeBaseHelper extends SQLiteOpenHelper {
    private static final int VERSION = 1;
    private static final String DATABASE_NAME = "crimeBase.db";

    public CrimeBaseHelper(Context context) {
        super(context, DATABASE_NAME, null, VERSION);
    }

//创建数据库（空的）
    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + CrimeDbSchema.CrimeTable.NAME + "(" +
                "_id integer primary key autoincrement , " +
                CrimeDbSchema.CrimeTable.Cols.UUID + "," +
                CrimeDbSchema.CrimeTable.Cols.TITLE + "," +
                CrimeDbSchema.CrimeTable.Cols.DATE + "," +
                CrimeDbSchema.CrimeTable.Cols.SOLVED + "," +
                CrimeDbSchema.CrimeTable.Cols.SUSPECT + ")"
        );
    }


    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
```

③调用Helper，来获得一个tabel（并且存于数据库中）
```java
//获得一个数据库tabel对象
mDataBase = new CrimeBaseHelper(mContext).getWritableDatabase(); //一般是在数据初始化的时候调用
```

④创建一个values对象---通过一个values对象来存
```java

private static ContentValues getContentValues(Crime crime) {
        ContentValues values = new ContentValues();
        values.put(CrimeDbSchema.CrimeTable.Cols.UUID, crime.getId() + "");
        values.put(CrimeDbSchema.CrimeTable.Cols.TITLE, crime.getTitle());
        values.put(CrimeDbSchema.CrimeTable.Cols.DATE, crime.getDate().getTime());
        values.put(CrimeDbSchema.CrimeTable.Cols.SOLVED, crime.isSolved());
        values.put(CrimeDbSchema.CrimeTable.Cols.SUSPECT,crime.getSuspect());
        return values;
```

⑤通过前面得到的数据库tabel对象和后面的values对象来对数据进行存入
```java
//初始化
public void updateCrime(Crime crime) {
        String uuidString = crime.getId() + "";
        ContentValues values = getContentValues(crime);

        mDataBase.update(CrimeDbSchema.CrimeTable.NAME, values, CrimeDbSchema.CrimeTable.Cols.UUID + "= ?", new String[]{uuidString});
    }
//插入
meDbSchema.CrimeTable.NAME, null, values);
```
⑥创建一个CursorWrapper类的子类，把“读取”操作封装起来

```java
public class CrimeCursorWrapper extends CursorWrapper {

    public CrimeCursorWrapper(Cursor cursor) {
        super(cursor);
    }

    public Crime getCrime() {
        String uuidString = getString(getColumnIndex(CrimeDbSchema.CrimeTable.Cols.UUID));
        String title = getString(getColumnIndex(CrimeDbSchema.CrimeTable.Cols.TITLE));
        long date = getLong(getColumnIndex(CrimeDbSchema.CrimeTable.Cols.DATE));
        int isSolved = getInt(getColumnIndex(CrimeDbSchema.CrimeTable.Cols.SOLVED));
        String suspect = getString(getColumnIndex(CrimeDbSchema.CrimeTable.Cols.SUSPECT));

        Crime crime = new Crime(UUID.fromString(uuidString));
        crime.setTitle(title);
        crime.setDate(new Date(date));
        crime.setSolved(isSolved != 0);
        crime.setSuspect(suspect);
        return crime;
    }
}
```
⑦使用该CursorWrapper子类的对象来遍历数据库和获取数据
```java
//获取一个cursor对象的方法
private CrimeCursorWrapper queryCrimes(String whereClause, String[] whereArgs) {
       Cursor cursor = mDataBase.query(
               CrimeDbSchema.CrimeTable.NAME,
               null,
               whereClause,
               whereArgs,
               null,
               null,
               null
       );
       return new CrimeCursorWrapper(cursor);
   }

//获取操作
public List<Crime> getCrimes() {
       List<Crime> crimes = new ArrayList<>();
       CrimeCursorWrapper cursor = queryCrimes(null, null);
       try {
           cursor.moveToFirst();
           while (!cursor.isAfterLast()) {
               crimes.add(cursor.getCrime());
               cursor.moveToNext();
           }
       } finally {
           cursor.close();
       }
       return crimes;
   }
```
