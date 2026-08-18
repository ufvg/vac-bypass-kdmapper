#pragma once

namespace Mutex
{
class Resource
{
  public:
    /// <summary>
    /// Initialize ERESOURCE
    /// </summary>
    /// <returns></returns>
    [[nodiscard]] NTSTATUS Initialize();

    /// <summary>
    /// Destrou ERESOURCE
    /// </summary>
    void Destroy();

    /// <summary>
    /// Acquires exclusive lock
    /// </summary>
    void LockExclusive();

    /// <summary>
    /// Acquires shared lock
    /// </summary>
    void LockShared();

    /// <summary>
    /// Unlock
    /// </summary>
    void Unlock();

    /// <summary>
    /// Get ERESOURCE
    /// </summary>
    /// <returns>ERESOURCE pointer</returns>
    __forceinline auto &GetResource() const
    {
        return this->_resource;
    }

  private:
    bool _initialized = false;
    LONG _refCount = 0;
    PERESOURCE _resource = nullptr;
};

} // namespace Mutex