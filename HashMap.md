## HashMap中KeySet方法原理

#### HashMap类中有一个Node内部类，该类实现了Entry接口

```java
static class Node<K,V> implements Map.Entry<K,V> {
        final int hash;
        final K key;
        V value;
        Node<K,V> next;

        Node(int hash, K key, V value, Node<K,V> next) {
            this.hash = hash;
            this.key = key;
            this.value = value;
            this.next = next;
        }

        public final K getKey()        { return key; }
        public final V getValue()      { return value; }
        public final String toString() { return key + "=" + value; }

        public final int hashCode() {
            return Objects.hashCode(key) ^ Objects.hashCode(value);
        }

        public final V setValue(V newValue) {
            V oldValue = value;
            value = newValue;
            return oldValue;
        }

        public final boolean equals(Object o) {
            if (o == this)
                return true;
            if (o instanceof Map.Entry) {
                Map.Entry<?,?> e = (Map.Entry<?,?>)o;
                if (Objects.equals(key, e.getKey()) &&
                    Objects.equals(value, e.getValue()))
                    return true;
            }
            return false;
        }
    }
```
#### HashMap类持有了一个内部类Node对象

```java
transient Node<K,V>[] table;
```
* 可以发现一个Hashmap是由一个链表数组组成，每个节点存在Key和Value,next

#### HashMap继承了AbstractMap类，该类中有一个Set对象

```java
transient Set<K>        keySet;
```
#### HashMap中有一个KeySet内部类，继承了AbstractSet类，类中实现了查找、删除、遍历等方法

```java
final class KeySet extends AbstractSet<K> {
       public final int size()                 { return size; }
       public final void clear()               { HashMap.this.clear(); }
       public final Iterator<K> iterator()     { return new KeyIterator(); }
       public final boolean contains(Object o) { return containsKey(o); }
       public final boolean remove(Object key) {
           return removeNode(hash(key), key, null, false, true) != null;
       }
       public final Spliterator<K> spliterator() {
           return new KeySpliterator<>(HashMap.this, 0, -1, 0, 0);
       }
       public final void forEach(Consumer<? super K> action) {
           Node<K,V>[] tab;
           if (action == null)
               throw new NullPointerException();
           if (size > 0 && (tab = table) != null) {
               int mc = modCount;
               for (Node<K, V> e : tab) {
                   for (; e != null; e = e.next)
                       action.accept(e.key);
               }
               if (modCount != mc)
                   throw new ConcurrentModificationException();
           }
       }
   }

//用来通过键值查找
public boolean containsKey(Object key) {
    return getNode(hash(key), key) != null;
}

final Node<K,V> getNode(int hash, Object key) {
    Node<K,V>[] tab; Node<K,V> first, e; int n; K k;
    if ((tab = table) != null && (n = tab.length) > 0 &&
        (first = tab[(n - 1) & hash]) != null) {
        if (first.hash == hash && // always check first node
            ((k = first.key) == key || (key != null && key.equals(k))))
            return first;
        if ((e = first.next) != null) {
            if (first instanceof TreeNode)
                return ((TreeNode<K,V>)first).getTreeNode(hash, key);
            do {
                if (e.hash == hash &&
                    ((k = e.key) == key || (key != null && key.equals(k))))
                    return e;
            } while ((e = e.next) != null);
        }
    }
    return null;
}

//用来删除节点
final Node<K,V> removeNode(int hash, Object key, Object value,
                           boolean matchValue, boolean movable) {
    Node<K,V>[] tab; Node<K,V> p; int n, index;
    if ((tab = table) != null && (n = tab.length) > 0 &&
        (p = tab[index = (n - 1) & hash]) != null) {
        Node<K,V> node = null, e; K k; V v;
        if (p.hash == hash &&
            ((k = p.key) == key || (key != null && key.equals(k))))
            node = p;
        else if ((e = p.next) != null) {
            if (p instanceof TreeNode)
                node = ((TreeNode<K,V>)p).getTreeNode(hash, key);
            else {
                do {
                    if (e.hash == hash &&
                        ((k = e.key) == key ||
                         (key != null && key.equals(k)))) {
                        node = e;
                        break;
                    }
                    p = e;
                } while ((e = e.next) != null);
            }
        }
        if (node != null && (!matchValue || (v = node.value) == value ||
                             (value != null && value.equals(v)))) {
            if (node instanceof TreeNode)
                ((TreeNode<K,V>)node).removeTreeNode(this, tab, movable);
            else if (node == p)
                tab[index] = node.next;
            else
                p.next = node.next;
            ++modCount;
            --size;
            afterNodeRemoval(node);
            return node;
        }
    }
    return null;
}

```

#### HashMap中有一个keySet方法，返回一个实现了Set接口的KeySet对象

```java
public Set<K> keySet() {
    Set<K> ks = keySet;
    if (ks == null) {
        ks = new KeySet();
        keySet = ks;
    }
    return ks;
}

```

#### 综上，我们可以通过返回的这个keySet内部类对象对map进行遍历和查询
