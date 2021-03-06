
package scifly.middleware.network;

import java.lang.reflect.Constructor;
import java.util.List;

import android.content.Context;
import android.net.wifi.WifiManager.ActionListener;
import android.os.SystemProperties;
import android.util.Log;

import com.google.android.collect.Lists;

public class WifiManagerGlobal {

    private static final String TAG = "WifiManagerGlobal";

    private static final String PLATFORM = SystemProperties.get("ro.board.platform", "");

    private static final String PLATFORM_MUJI = "muji";

    private static final String PLATFORM_MADISON = "madison";

    private static final String PLATFORM_MESON8 = "meson8";

    private static final String PLATFORM_MONET = "monet";

    private IWifiManager mWifiManagerImpl;

    public WifiManagerGlobal(Context context) {
        final String clsName;
        // mstar 4.4
        if (PLATFORM.equals(PLATFORM_MADISON)) {
            clsName = "scifly.middleware.network.mstar.kitkat.WifiManagerImpl";
            // mstar 5.0&&mstar5.1
        } else if (PLATFORM.equals(PLATFORM_MUJI) || PLATFORM.equals(PLATFORM_MONET)) {
            clsName = "scifly.middleware.network.mstar.lollipop.WifiManagerImpl";
            // 805
        } else if (PLATFORM.equals(PLATFORM_MESON8)) {
            clsName = "scifly.middleware.network.amlogic.kitkat.WifiManagerImpl";
        } else {
            Log.w(TAG, "unknown platform");
            throw new RuntimeException("unknown platform");
        }

        Class<?> c = null;
        Constructor<?> constructor = null;
        try {
            c = Class.forName(clsName);
            constructor = c.getConstructor(Context.class);
            mWifiManagerImpl = (IWifiManager) constructor.newInstance(context);
        } catch (Exception e) {
            Log.e(TAG, "exception while new instance " + clsName, e);
            throw new RuntimeException("exception while new instance " + clsName);
        }
    }

    public void connect(WifiConfig config, ActionListener listener) {
        if (mWifiManagerImpl == null) {
            return;
        }
        mWifiManagerImpl.connect(config, listener);
    }

    public void save(WifiConfig config, ActionListener listener) {
        if (mWifiManagerImpl == null) {
            return;
        }
        mWifiManagerImpl.save(config, listener);
    }

    public List<WifiConfig> getConfiguredNetworks() {
        if (mWifiManagerImpl == null) {
            return Lists.newArrayList();
        }
        return mWifiManagerImpl.getConfiguredNetworks();
    }

    public WifiConfig getConfiguredNetworks(int networkId) {
        if (mWifiManagerImpl == null) {
            return null;
        }
        return mWifiManagerImpl.getConfiguredNetworks(networkId);
    }

    public IpConfig getConfiguration() {
        if (mWifiManagerImpl == null) {
            return null;
        }
        return mWifiManagerImpl.getConfiguration();
    }

    public void setConfiguration(IpConfig config) {
        if (mWifiManagerImpl == null) {
            return;
        }
    }
}
